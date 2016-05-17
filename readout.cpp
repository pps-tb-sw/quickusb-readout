#include "stdafx.h"
#include "windows.h"
#include "quickusb.h"
#include <iostream>
#include <fstream>
#include "PlatformIndependentTimer.h"
#include "APIUSB.h"

using namespace std;

ofstream myfile ("example.bin", ios::out | ios::app | ios::binary | ios::ate);
static bool writing = false;

const int NumBuffers = 8;
const int BufferByteSize = 65536;
	
QBULKSTREAM   BulkStream[NumBuffers];

///////////////////////////////////////
// The BulkStream completion routine //
///////////////////////////////////////
QVOIDRETURN CompletionRoutine(PQBULKSTREAM BulkStream)
{
    if (!BulkStream) { return; }

    // Check for errors
    if (BulkStream->Error) {
        cout << "--> CR: ERROR! Failed with error " << BulkStream->Error << " (" << BulkStream->BytesTransferred << " of " << BulkStream->BytesRequested << " bytes)" << endl;
    } else {
        //cout << "--> CR: Completed request for " << BulkStream->BytesTransferred << " bytes" << endl;
    }

	while (true) {
		if (writing) continue;
		writing = true;
		
		/*for (unsigned short i=0; i<NumBuffers; i++) {
		//const unsigned short i = 2; //FIXME for debugging
			for (unsigned int j=0; j<BufferByteSize/2; j++) {
				unsigned short word = (BufferArray[i][2*j]<<8)+BufferArray[i][2*j+1]; // group the two bytes into a 16-bit word
				if (word==0x00ff) continue;
				myfile << word;
//std::cout << std::hex << word << std::endl;
			}
		}*/
		for (unsigned int j=0; j<BufferByteSize/2; j++) {
			unsigned short word = (BulkStream->Buffer[2*j]<<8)+BulkStream->Buffer[2*j+1]; // group the two bytes into a 16-bit word
			if (word==0x00ff) continue;
			myfile << word;
			std::cout << std::hex << word << std::endl; //FIXME delete me!!
		}
		//std::cout << BulkStream->StreamID << " --- " << BulkStream->RequestID << " --- " << BulkStream->Reserved << std::endl;
		//myfile << BufferArray;
		writing = false;
		
		return;
	}
}


int main(int argc, char* argv[])
{
	// Variables
    QCHAR   nameList[1024];
    QRESULT qResult;
    QULONG  qusbError;
    QHANDLE hDevice;
    QBYTE streamID;
	
    PlatformIndependentTimer timer;
    double tElapsed;

	if (myfile.is_open()){
		cout<<"File 'namefile.bin' created" << endl;
	}
	else {
		cout << "Unable to open/create 'filename'"<<endl;
		return 0;
	}
	

	printf("Hello QuickUSB World!\n");

    // Query connected modules
    qResult = QuickUsbFindModules(nameList, 1024);
    if (!qResult) {
        QuickUsbGetLastError(&qusbError);
        cout << "QuickUSB Error: " << qusbError << endl;
        return qusbError;
    }



    // Open the first module
    qResult = QuickUsbOpen(&hDevice, nameList);
    if (!qResult) {
        QuickUsbGetLastError(&qusbError);
        cout << "QuickUSB Error: " << qusbError << endl;
        return qusbError;
    }

    // Setting timeout
	QuickUsbSetTimeout (hDevice, 1000);
	
	
	QuickUsbWriteSetting(hDevice, 1, 1); // 16 bits words
	QuickUsbWriteSetting(hDevice, 2, 32768+200); // readout register address

    // Start timing
    timer.Start();
	
    // Begin streaming data
    //qResult = QuickUsbReadBulkDataStartStream(hDevice, BufferArray, NumBuffers, BufferByteSize, &CompletionRoutine, 0, &streamID, 8, 4);
	qResult = QuickUsbReadBulkDataStartStream(hDevice, 0, NumBuffers, BufferByteSize, &CompletionRoutine, 0, &streamID, 8, 4);
    if (!qResult) {
        QuickUsbGetLastError(&qusbError);
        cout << "QuickUSB Error: " << qusbError << endl;
        return qusbError;
    }
	
	cout << "Streaming data for 5 seconds..." << endl;
	
    // Acquire data in the background for 5 seconds
    do {
        // Check if our time has elapsed
        tElapsed = timer.GetElapsedTimeInSeconds();
    } while (tElapsed < 5.0);
	
    // Stop the data aquisition, but do not stop the stream from the buffer to file
    cout << "Stop Data Aquisition!" << endl;
    qResult = QuickUsbStopStream(hDevice, streamID, TRUE);
    if (!qResult) {
        QuickUsbGetLastError(&qusbError);
        cout << "QuickUSB Error: " << qusbError << endl;
        return qusbError;
    }
	
	// Stop the data stream
    cout << "Stop Data Streaming from buffer to file" << endl;
	
	// Stop the data stream, but block this time
    qResult = QuickUsbStopStream(hDevice, streamID, FALSE);
    if (!qResult) {
        QuickUsbGetLastError(&qusbError);

        // Check the error
        if (qusbError == QUICKUSB_ERROR_NOT_STREAMING) {
            // The stream has already finished shutting down.  This is not an error
            // because we want the stream to be stopped, so continue on normally.
        } else {
            cout << "QuickUSB Error: " << qusbError << endl;
        }
    }

    // Close the device
    qResult = QuickUsbClose(hDevice);
    if (!qResult) {
        QuickUsbGetLastError(&qusbError);
        cout << "QuickUSB Error: " << qusbError << endl;
        return qusbError;
    }
	
    // Display statistics
    timer.Stop();
    tElapsed = timer.GetElapsedTimeInSeconds();

	myfile.close();
	
    // Exit without error
    return 0;

}



