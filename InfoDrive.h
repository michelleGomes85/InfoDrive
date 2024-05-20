#pragma once

#include <string>
#include <optional>

using namespace std;

class InfoDrive {

public:
	const int NUMBER_LETTER_ALPHABET = 26;
	const char DRIVE_LETTER_A = 'A';
	const char DRIVE_LETTER_Z = 'Z';
	const int INVALID_DRIVE_ID = -1;


	const static int SIZE_KB = 1024;
	const static int SIZE_MB = 1048576;
	const static int SIZE_GB = 1073741824;

	const char NULL_CHARACTER = '\0';

	const string
		NEW_LINE = "\n",
		TAB = "\t",
		EQUAL_SIGN = " = ",
		TWO_POINTS = ": ",
		LABEL_NUMBER_DRIVES = "Numero de Drives",
		LABEL_SYSTEM_DRIVES = "Drives do Sistema",
		LABEL_CURRENT_DRIVE = "Drive atual",
		LABEL_DRIVE = "Drive ",
		LABEL_TOTAL_SPACE = "Tamanho Total",
		LABEL_FREE_SPACE = "Espaco Livre",
		LABEL_TOTAL_CLUSTERS = "Total de Clusters",
		LABEL_AVAILABLE_CLUSTERS = "Clusters Disponiveis",
		LABEL_CLUSTER_SIZE = "Tamanho do Cluster",
		LABEL_SECTOR_SIZE = "Tamanho do Setor",
		LABEL_DRIVE_NOT_FOUND = "nao encontrado!!",
		OR = " ou ",
		CLUSTER = " Clusters ";

	InfoDrive() = default;

	/* 
		Obtem os dados abaixo sobre um drive (unidade logica ou fisica de armazenamento):

		1. espaco total do disco;
		2. espaco livre do disco;
		3. numero total de unidades de alocacao (cluster);
		4. numero total de unidades de alocacao disponiveis;
		5. tamanho de cada unidade de alocacao;
		6. tamanho do setor.

		Se o drive for valido, ou seja, corresponde a uma unidade de armazenamento existente no sistema, 
		a funcao retorna um objeto InfoDrive, encapsulado em um objeto optional2, com os valores obtidos do drive, 
		caso contrario retorna um objeto optional sem um objeto InfoDrive. 
		Se nenhuma letra de identificacao do drive for especificada, serr obtido as informacoes da unidade C.
	*/
	optional<InfoDrive> infoDrive(char drive = 'C');

	// Obtem a identificacao do drive atual. Em caso de erro retorna NULL_CHARACTER.
	char currentDrive();

	// Obtem o numero de drives disponiveis no sistema.
	unsigned numberOfDrives();

	/*  
		Obtem a relacao de drives disponiveis no sistema. 
		Por exemplo, se as unidades disponiveis sao C:, D:, E: e F:, retorna a string 'C:D:E:F:'.
	*/
	string drives();

	// Obtem a letra de identificacao do drive.
	char getDriveID();

	// Obtem o espaco total do disco.
	unsigned long long getTotalSize();

	// Obtem o espaco livre do disco.
	unsigned long long getFreeSize();

	// Obtem o numero total de clusters.
	unsigned getTotalCluster();

	// Obtem o numero total de clusters disponiveis.
	unsigned getAvailableCluster();

	// Obtem o tamanho de cada unidade de alocacao.
	unsigned getClusterSize();

	// Obtem o tamanho do setor.
	unsigned getSectorSize();

	// Relata as informacoes sobre os drives do sistema.
	int relatorio();

private:

	/*	
		Obtem o numero e a relacao das letras dos drives disponiveis no sistema.
		Retorna o numero de drives e armazena a relacao das letras dos drives no parametro formal letterOfDrives.
	*/
	unsigned getDrives(string& letterOfDrives);

	/* 
		Converte a letra de identificacao do drive em um numero. 
		O drive A = 1, B = 2, C = 3, e assim por diante. 
		Se a letra de identificacao do drive for invalida retorna INVALID_DRIVE_ID.
	*/
	int convertDriveID(char drive);

	/* 
		Converte o numero de identificacao do drive em uma letra. 
		O drive 1 = A, 2 = B, 3 = C, e assim por diante. 
		Se o numero de identificacao do drive for invalido retorna NULL_CHARACTER.
	*/
	char convertDriveID(unsigned drive);

	char driveID = 'C'; // Letra de identificacao do drive.

	unsigned long long
		totalSize = 0, // espaco total do disco
		freeSize = 0; // espaco livre do disco
	
	unsigned
		totalCluster = 0, // numero total de clusters
		availableCluster = 0, // numero total de clusters disponiveis
		clusterSize = 0, // tamanho de cada unidade de alocacao
		sectorSize = 0; // tamanho do setor

}; // class InfoDrive