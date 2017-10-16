#include "stdafx.h"
#include "attributes.h"

using namespace std;

bool getAvailableAttributes(IMAQdxSession sessionID) {
	IMAQdxError status;

	// the number of the available attributes
	uInt32 attrCount;

	// Specify the branch of the attribute tree to enumerate.  
	char* root = NULL;

	// get the names and the accesibilities of the attributes
	status = IMAQdxEnumerateAttributes2(sessionID, NULL, &attrCount, root, IMAQdxAttributeVisibilitySimple);
	if (status != IMAQdxErrorSuccess) {
		imaqdxError(status);
		puts("Fail to get available attributes.");
		return false;
	}

	IMAQdxAttributeInformation attrInfoArr[256];
	status = IMAQdxEnumerateAttributes2(sessionID, attrInfoArr, &attrCount, root, IMAQdxAttributeVisibilitySimple);
	if (status != IMAQdxErrorSuccess) {
		imaqdxError(status);
		puts("Fail to get available attributes.");
		return false;
	}

	// write the available attributes into a txt file
	ofstream attributeFile;
	string directory = "C:/git/Acquisition/C/MIAcquire/";
	string fileName = "available attributes.txt";
	attributeFile.open(directory + fileName);
	for (uInt32 i = 0; i < attrCount; i++) {
		IMAQdxAttributeInformation attribute = attrInfoArr[i];
		bool32 readable;
		bool32 writable;

		IMAQdxIsAttributeReadable(sessionID, attribute.Name, &readable);
		IMAQdxIsAttributeWritable(sessionID, attribute.Name, &writable);

		string read = readable == 1 ? "readable" : "unreadable";
		string write = writable == 1 ? "writable" : "unwritable";
		attributeFile << setw(50) << attribute.Name << "\t" << read 
			<< "\t" << write << "\n";
	}
	attributeFile.close();

	return true;
}

uInt32 getImageHeight(IMAQdxSession session) {
	uInt32 height;
	IMAQdxGetAttribute(
		session, 
		"Height", 
		IMAQdxValueTypeU32, 
		&height);

	return height;
}

uInt32 getImageWidth(IMAQdxSession session) {
	uInt32 width;
	IMAQdxGetAttribute(
		session, 
		"Width", 
		IMAQdxValueTypeU32, 
		&width);

	return width;
}