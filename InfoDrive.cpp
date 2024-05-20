#include <iostream>
#include <string>
#include <locale> // Para std::locale
#include <sstream> // Para std::stringstream
#include <iomanip> // Para std::fixed e std::setprecision

#include <direct.h>
#include "InfoDrive.h"

optional<InfoDrive> InfoDrive::infoDrive(char drive) {

	InfoDrive infoDrive;

	int driveNumber = convertDriveID(drive);

	if (_chdrive(driveNumber) == 0) {

		infoDrive.driveID = drive;

		struct _diskfree_t diskInfo;

		if (_getdiskfree(driveNumber, &diskInfo) == 0) {

			infoDrive.clusterSize = diskInfo.sectors_per_cluster * diskInfo.bytes_per_sector;

			infoDrive.totalCluster = diskInfo.total_clusters;
			infoDrive.availableCluster = diskInfo.avail_clusters;
			infoDrive.sectorSize = diskInfo.bytes_per_sector;

			infoDrive.totalSize = static_cast<unsigned long long>(infoDrive.totalCluster) * infoDrive.clusterSize;
			infoDrive.freeSize = static_cast<unsigned long long>(infoDrive.availableCluster) * infoDrive.clusterSize;

			return optional<InfoDrive>(infoDrive);
		}
	}

	return optional<InfoDrive>();
}

char InfoDrive::currentDrive() {
	unsigned numeroDriveCorrente = _getdrive();
	return convertDriveID(numeroDriveCorrente);
}

unsigned InfoDrive::numberOfDrives() {

	unsigned drivesMask = _getdrives();
	unsigned count = 0;

	for (int drive = 0; drive < NUMBER_LETTER_ALPHABET; ++drive) {

		if (drivesMask & 1)
			count++;

		drivesMask >>= 1;
	}

	return count;
}

string InfoDrive::drives() {

	string drives;

	getDrives(drives);

	return drives;
}

char InfoDrive::getDriveID() {
	return driveID;
}

unsigned long long InfoDrive::getTotalSize() {
	return totalSize;
}

unsigned long long InfoDrive::getFreeSize() {
	return freeSize;
}

unsigned InfoDrive::getTotalCluster() {
	return totalCluster;
}

unsigned InfoDrive::getAvailableCluster() {
	return availableCluster;
}

unsigned InfoDrive::getClusterSize() {
	return clusterSize;
}

unsigned InfoDrive::getSectorSize() {
	return sectorSize;
}

unsigned InfoDrive::getDrives(string& letterOfDrives) {

	unsigned drivesMask = _getdrives();
	unsigned count = 0;

	for (unsigned drive = 0; drive < NUMBER_LETTER_ALPHABET; ++drive) {
		if (drivesMask & 1)		{
			char driveLetter = convertDriveID(drive + 1);
			letterOfDrives += driveLetter;
			count++;
		}

		drivesMask >>= 1;
	}

	return count;
}

int InfoDrive::convertDriveID(char drive) {
	
	if (drive >= DRIVE_LETTER_A && drive <= DRIVE_LETTER_Z)
		return static_cast<int>(drive - DRIVE_LETTER_A + 1);

	return INVALID_DRIVE_ID;
}

char InfoDrive::convertDriveID(unsigned drive) {

	if (drive >= 1 && drive <= NUMBER_LETTER_ALPHABET)
		return static_cast<char>(DRIVE_LETTER_A + drive - 1);

	return NULL_CHARACTER;
}

string formatarNumero(double numero) {

	locale loc("pt_BR.UTF-8");
	stringstream ss;
	ss.imbue(loc);
	ss << fixed << setprecision(2) << numero;
	return ss.str();
}

string formatarNumeroInt(unsigned long long numero) {
	locale loc("pt_BR.UTF-8");
	stringstream ss;
	ss.imbue(loc);
	ss << fixed << numero;
	return ss.str();
}

string humanReadableSize(const unsigned long long size, bool bytes) {
	
	const string BYTE = " Bytes";
	const string KB = " KB";
	const string MB = " MB";
	const string GB = " GB";

	if (size < InfoDrive::SIZE_KB || bytes)
		return formatarNumeroInt(size) + BYTE;
	else if (size < InfoDrive::SIZE_MB)
		return formatarNumero(static_cast<double>(size) / InfoDrive::SIZE_KB) + KB;
	else if (size < InfoDrive::SIZE_GB)
		return formatarNumero(static_cast<double>(size) / InfoDrive::SIZE_MB) + MB;
	else
		return formatarNumero(static_cast<double>(size) / InfoDrive::SIZE_GB) + GB;
}

int InfoDrive::relatorio() {

	setlocale(LC_ALL, "pt-BR");

	InfoDrive infoDrive;

	unsigned numDrives = infoDrive.numberOfDrives();

	string driveLetters = infoDrive.drives();

	char currentDrive = infoDrive.currentDrive();

	cout << NEW_LINE + TAB + LABEL_NUMBER_DRIVES + EQUAL_SIGN << numDrives << endl;
	cout << NEW_LINE + TAB + LABEL_SYSTEM_DRIVES + EQUAL_SIGN;

	for (unsigned int i = 0; i < numDrives; i++)
		cout << driveLetters[i] << TWO_POINTS;

	cout << NEW_LINE + NEW_LINE + TAB + LABEL_CURRENT_DRIVE + EQUAL_SIGN << currentDrive << endl;

	for (int i = 0; i < driveLetters.length(); ++i) {

		char driveLetter = driveLetters[i];
		optional<InfoDrive> driveInfo = infoDrive.infoDrive(driveLetter);

		cout << endl;

		if (driveInfo.has_value()) {
			InfoDrive drive = driveInfo.value();

			cout << LABEL_DRIVE << driveLetter << TWO_POINTS << endl << endl;

			unsigned totalSize = drive.getTotalSize();
			unsigned freeSize = drive.getFreeSize();
			unsigned totalCluster = drive.getTotalCluster();
			unsigned availableCluster = drive.getAvailableCluster();
			unsigned clusterSize = drive.getClusterSize();
			unsigned sectorSize = drive.getSectorSize();

			cout << TAB + LABEL_TOTAL_SPACE + TWO_POINTS << humanReadableSize(totalSize, true);
			(totalSize >= SIZE_KB) ? cout << OR << humanReadableSize(drive.getTotalSize(), false) << endl : cout << endl;

			cout << TAB + LABEL_FREE_SPACE + TWO_POINTS << humanReadableSize(freeSize, true);
			(freeSize >= SIZE_KB) ? cout << OR << humanReadableSize(drive.getFreeSize(), false) << endl : cout << endl;

			cout << NEW_LINE + TAB + LABEL_TOTAL_CLUSTERS + TWO_POINTS << formatarNumeroInt(totalCluster) << CLUSTER << endl;
			cout << TAB + LABEL_AVAILABLE_CLUSTERS + TWO_POINTS << formatarNumeroInt(availableCluster) << CLUSTER << endl;

			cout << NEW_LINE + TAB + LABEL_CLUSTER_SIZE + TWO_POINTS << humanReadableSize(clusterSize, true);
			(clusterSize >= SIZE_KB) ? cout << OR << humanReadableSize(drive.getClusterSize(), false) << endl : cout << endl;

			cout << TAB + LABEL_SECTOR_SIZE + TWO_POINTS << humanReadableSize(sectorSize, true);
			(sectorSize >= SIZE_KB) ? cout << OR << humanReadableSize(drive.getSectorSize(), false) << endl : cout << endl;
		}
		else
			cout << LABEL_DRIVE << driveLetter << LABEL_DRIVE_NOT_FOUND << endl;
	}

	return EXIT_SUCCESS;
}

int main() {
	return InfoDrive(). relatorio();
}