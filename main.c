//***********************************************************//
//                      [ Source Code ]
//
// Institution       : Institut Teknologi Bandung
// Name              : Muhammad Iqbal Fauzan Aulia - 13217051
//					   Giovanni Philip Santoso - 13217052
//					   Tyfan Juliano Hioesman - 13217063
//					   Hansen Devin Hotama - 13217064
//					   Friendi Sofyan - 13217069
//
// File Name         : main.c
// Dependency        : stdio.h, stdlib.h, string.h
//
// Description:
//     Menghasilkan jadwal praktikum semester genap dan juga
//jadwal asisten sesuai input user yang telah tervalidasi dari
//berbagai ketentuan dan kondisi yang mungkin
//
// Status:
// 1. <Tyfan Juliano> - <13217063> : Create main program
//and debug it
// 2. <Tyfan Juliano> - <13217063> : Create rule function
//and debug it
// 3. <Giovanni Philip Santoso> - <13217052> : Create New file
//and save function and debug it
// 4. <Friendi Sofyan> - <13217069> : Create LoadFile function
//and debug it
// 5. <Hansen Devin Hotama> - < 13217064> : Create showS and FillS
//function and debug it
// 6. <Muhammad Iqbal Fauzan Aulia> - <13217051> : Create showA
//and FillA function and debug it
//***********************************************************//



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void newfile(char fileschd[],char fileasst[]); //1
void loadfile(char fileschd[],char fileasst[],char lab1[][5][10],char lab2[][5][10],char lab3[][5][10],char lss[][5][10],char Alab1[][5][2],char Alab2[][5][2],char Alab3[][5][2],char Alss[][5][2]); //2
void showS(char lab1[][5][10],char lab2[][5][10],char lab3[][5][10],char lss[][5][10]); //3
void fillS(int modul[3][10], char lab1[][5][10],char lab2[][5][10],char lab3[][5][10],char lss[][5][10]); //4
void showA(char Alab1[][5][2], char Alab2[][5][2], char Alab3[][5][2],
	char Alss[][5][2]); //5
int fillA(char lab1[][5][10],char lab2[][5][10],char lab3[][5][10],
	char lss[][5][10], char *Alab1[][5][2],char *Alab2[][5][2],
	char *Alab3[][5][2], char *Alss[][5][2]); //6
//void autoS();
//void autoA();
void rule(char lab1[][5][10],char lab2[][5][10],char lab3[][5][10],char lss[][5][10],char Alab1[][5][2],char Alab2[][5][2],char Alab3[][5][2],char Alss[][5][2],char filerule[],int modul[][10]); //9
void save(char lab1[][5][10],char lab2[][5][10],char lab3[][5][10],char lss[][5][10],char Alab1[][5][2],char Alab2[][5][2],char Alab3[][5][2],char Alss[][5][2],char fileschd[],char fileasst[]); //10

void printLab(char Alab[]){
	if (Alab[0] == ' '){
			printf("            |");
		} else if ((Alab[0] != ' ') && (Alab[1] == ' ')){
			printf("     %c      |", Alab[0]);
		} else if ((Alab[0] != ' ') && (Alab[1] != ' ')){
			printf("    %c, %c    |", Alab[0], Alab[1]);
		}
}

void printS(char lab[]){
	if (strcmp(lab, " ")==0){
			printf("            |");
		} else {
			printf("%12s|", lab);
		}
}

void getSchedule(char *baris,char lab1[16][5][10],char lab2[16][5][10],char lab3[16][5][10], char lss[16][5][10],
                 int i, int j){
        char *token;
        token = strtok(baris,";");
        strcpy(lab1[i][j],token);
        token = strtok(NULL,";");
        strcpy(lab2[i][j],token);
        token = strtok(NULL,";");
        strcpy(lab3[i][j],token);
        token = strtok(NULL,";");
        strcpy(lss[i][j],token);
        free(token);
        //printf("\n%8s %8s %8s %8s\n",lab1[i][j],lab2[i][j],lab3[i][j],lss[i][j]);
}

void getAsisten(char *baris,char Alab1[16][5][2],char Alab2[16][5][2],char Alab3[16][5][2], char Alss[16][5][2],
                 int i, int j){
        char *token;
        token = strtok(baris,",");
        Alab1[i][j][0] = *token;
        token = strtok(NULL,";");
        Alab1[i][j][1] = *token;

        token = strtok(NULL,",");
        Alab2[i][j][0] = *token;
        token = strtok(NULL,";");
        Alab2[i][j][1] = *token;

        token = strtok(NULL,",");
        Alab3[i][j][0] = *token;
        token = strtok(NULL,";");
        Alab3[i][j][1] = *token;

        token = strtok(NULL,",");
        Alss[i][j][0] = *token;
        token = strtok(NULL,";");
        Alss[i][j][1] = *token;

        free(token);
    //printf("\n%8s %8s %8s %8s\n",lab1[i][j],lab2[i][j],lab3[i][j],lss[i][j]);
}

int main(){
	//deklarasi variabel
	int w,d,n,l; // w = weel ; d = day ; n = asisten ke ; l = length character
	int input1, input2; // input1 memilih new file atau loiad file, input 2 memilih properti

	int modul[3][10];
	//[0][..] : biomed; [1][...] : elka ; [2][..] : pmc ;
	//[0][0] = EB2200-A ; [0][1] = EB2200-B
	//[1][0] = EL2205-A1; [1][1] = EL2205-A2; [1][2] = EL2205-B1;
	//[1][3] = EL2205-B2; [1][4] = EL2205-C1; [1][5] = EL2205-C2
	//[2][0] = EL2208-A1; [2][1] = EL2208-A2; [2][2] = EL2208-A1
	//[2][3] = EL2208-B1; [2][4] = EL2208-B2; [2][5] = EL2208-B3; [2][6] = EL2208-C

	//array schedule
	char lab1[16][5][10]; //labX[week ke ...][hari (senin = 0, jumat = 4)][strlength] ; 3<=week<=15
	char lab2[16][5][10];
	char lab3[16][5][10];
	char lss[16][5][10];

	//array assistant
	char Alab1[16][5][2]; //labX[week ke ...][hari (senin = 0, jumat = 4)][asisten ke...][strlength] ; 3<=week<=15
	char Alab2[16][5][2];
	char Alab3[16][5][2];
	char Alss[16][5][2];

	char fileschd[100]; //file schedule
	char fileasst[100]; //file assistant
	char filerule[100];
	//deklarasi variabel

	//algoritma
	printf("Menu : \n");
	printf("1. Buat proyek baru. \n");
	printf("2. Muat proyek lama. \n");
	printf("3. keluar. \n");
	printf("Masukan pilihan proyek :");
	scanf("%d",&input1);
	printf("\n");
	//validasi input1
	while (input1<1 || input1>3){
		printf("Pilihan tidak tersedia!! \n");
		printf("Masukan pilihan proyek : ");
		scanf("%d",&input1);
		printf("\n");
	}

	if (input1 != 3){
		//pilihan new file
		if (input1 == 1){
			printf("Masukan nama file jadwal praktikum baru : ");
			scanf("%s",&fileschd);
			printf("Masukan nama file asisten praktikum baru : ");
			scanf("%s",&fileasst);
			//membuat file baru
			newfile(fileschd,fileasst);
			for(int i=1;i<=16;i++){
                for(int j=0;j<=4;j++){
                    strcpy(lab1[i][j]," ");
                    strcpy(lab2[i][j]," ");
                    strcpy(lab3[i][j]," ");
                    strcpy(lss[i][j]," ");
                    Alab1[i][j][0] = ' ';
                    Alab1[i][j][1] = ' ';
                    Alab2[i][j][0] = ' ';
                    Alab2[i][j][1] = ' ';
                    Alab3[i][j][0] = ' ';
                    Alab3[i][j][1] = ' ';
                    Alss[i][j][0] = ' ';
                    Alss[i][j][1] = ' ';
                }
			}
		}

		//pilihan load file
		if (input1 == 2){
			printf("Masukan nama file jadwal praktikum : ");
			scanf("%s",&fileschd);
			printf("Masukan nama file asisten praktikum : ");
			scanf("%s",&fileasst);
			//memuat file lama
			loadfile(fileschd,fileasst,lab1,lab2,lab3,lss,Alab1,Alab2,Alab3,Alss);
		}
		printf("\n");
		printf("Opsi yang tersedia : \n");
		printf("1. Tampilkan jadwal praktikum. \n");
		printf("2. Ubah jadwal praktikum. \n");
		printf("3. Tampilkan jadwal asisten. \n");
		printf("4. Ubah jadwal asisten. \n");
		printf("5. Membuat jadwal praktikum otomatis. \n");
		printf("6. Membuat jadwal asisten otomatis. \n");
		printf("7. Periksa jadwal praktikum dan jadwal asisten \n");
		printf("8. Simpan pekerjaan dan keluar. \n");
		printf("Masukan pilihan opsi pekerjaan : \n");
		scanf("%d",&input2);
		//validasi input2
		while(input2 < 1  || input2 > 8){
			printf("\n");
			printf("Pilihan tidak tersedia!! \n");
			printf("Masukan pilihan opsi pekerjaan : \n");
			scanf("%d",&input2);
			printf("\n");
		}

		while(input2 != 8){

			//pilihan 1
			if(input2 == 1){
				showS(lab1,lab2,lab3,lss);
			}
			//pilihan 2
			if(input2 == 2){
				fillS(modul,lab1,lab2,lab3,lss);
			}
			//pilihan 3
			if(input2 == 3){
				showA(Alab1,Alab2,Alab3,Alss);
			}
			//pilihan 4
			if(input2 == 4){
				fillA(lab1,lab2,lab3,lss,&Alab1,&Alab2,&Alab3,&Alss);
			}
			//pilihan 5
			//pilihan 6
			//pilihan 7
			if(input2 == 7){
				printf("masukan nama file hari berhalangan : ");
				scanf("%s",&filerule);
				rule(lab1,lab2,lab3,lss,Alab1,Alab2,Alab3,Alss,filerule,modul);
			}
			printf("\n");
			printf("Masukan pilihan opsi pekerjaan : \n");
			scanf("%d",&input2);
		}

		save(lab1,lab2,lab3,lss,Alab1,Alab2,Alab3,Alss,fileschd,fileasst);
		printf("keluar dari program...");
	}

	//pilihan keluar
	else{
		printf("keluar dari program...");
	}

}

void newfile(char fileschd[],char fileasst[]){
	//deskripsi : membuat 2 file baru (file asisten dan file jadwal) dengan nama filseschd  dan fileasst
	FILE *fp1;
	fp1 = fopen(fileschd, "w+");
	fclose(fp1);

	FILE *fp2;
	fp2 = fopen(fileasst, "w+");
	fclose(fp2);
}

void loadfile(char fileschd[],char fileasst[],char lab1[][5][10],char lab2[][5][10],char lab3[][5][10],char lss[][5][10],char Alab1[][5][2],char Alab2[][5][2],char Alab3[][5][2],char Alss[][5][2]){
    FILE *fp1, *fp2;
    fp1 = fopen(fileschd,"r");
    int i=1, j=0;
    do{
        char baris[1024];
        fgets(baris, 1024, (FILE*)fp1);
        //printf(baris);
        getSchedule(baris, lab1, lab2, lab3, lss, i, j);
        j++;
        if(j > 4){
            i++;
            j=0;
        }
    }while((!feof((FILE*)fp1)) && (i<=16));
    fclose(fp1);

    fp2 = fopen(fileasst,"r");
    i=1; j=0;
    do{
        char baris[1024];
        fgets(baris, 1024, (FILE*)fp2);
        //printf(baris);
        getAsisten(baris, Alab1, Alab2, Alab3, Alss, i, j);
        j++;
        if(j > 4){
            i++;
            j=0;
        }
    }while((!feof((FILE*)fp1)) && (i<=16));
    fclose(fp1);
}


void showS(char lab1[][5][10],char lab2[][5][10],char lab3[][5][10],char lss[][5][10]){
int week, day;
	printf("|--------------------------------------------------------------------|\n");
	printf("|Ruang Praktikum |    LAB1    |    LAB2    |    LAB3    |    LSS     |\n");
	printf("|----------------|------------|------------|------------|------------|\n");
	printf("|Minggu |  Hari  |------------|------------|------------|------------|\n");
	printf("|-------|--------|------------|------------|------------|------------|\n");
	for (week = 3; week <= 15; week++){

		for (day = 0; day <= 4; day ++){
            printf("|   %d   |", week);
			switch (day){
				case 0 : printf(" Senin  |");
				break;
				case 1 : printf(" Selasa |");
				break;
				case 2 : printf(" Rabu   |");
				break;
				case 3 : printf(" Kamis  |");
				break;
				case 4 : printf(" Jumat  |");
				break;
				default : printf(" Salah  |");
			}
			printS(lab1[week][day]);
			printS(lab2[week][day]);
			printS(lab3[week][day]);
			//printS(lss[week][day]);
			printf("\n");
		}
		printf("|--------------------------------------------------------------------| \n");
	}
}


void fillS(int modul[3][10], char lab1[][5][10],char lab2[][5][10],char lab3[][5][10],char lss[][5][10]){

int *elek[16][5] = {};//membandingkan agar tidak ada praktikum PMC dan Elektronika di hari yang sama
	int *pmc[16][5] = {};
    int week,day; //mencegah bug dan ambiguasi
    int kodeprak; //EL2208:1/EL2205:2/EB2200:3
    int rombongan; //A3:1/B3:2/A:3/B:4/C:5/A1:6/A2:7/B1:8/B2:9/C1:10/C2:11
    int lab; //1-3:1-3/lss:4
    int i,j = 0;

while(week != 17){
        printf("Masukan '17' untuk mengakhiri fills \n");
        printf("Minggu ke : \n");
        scanf("%d", &week);
            while (week<1 || week>17){
            printf("Input minggu salah \n");
            printf("Minggu ke : \n");
            scanf("%d",&week);
            }
                if (week == 17){
                printf("Kembali ke menu 2: \n");
                }
                else{//jika minggu 1-16
                printf("Kode praktikum (EL2208:1/EL2205:2/EB2200:3): \n");
                scanf("%d", &kodeprak);
                        while (kodeprak<1 || kodeprak>3){
                        printf("Input kode praktikum salah \n");
                        printf("Kode praktikum (EL2205:1/EL2208:2/EB2200:3) : \n");
                        scanf("%d",&kodeprak);
                        }
                    if (kodeprak == 3)//EB220
                    {
                        printf("Rombongan (A:3,B:4) :\n");
                        scanf("%d",&rombongan);
                            while (rombongan < 3 || rombongan > 4){
                            printf("Input rombongan salah \n");
                            printf("Rombongan (A:3,B:4) :\n");
                            scanf("%d",&rombongan);
                            }
                                printf("Hari :(Selasa:1,Kamis:3) \n");
                                scanf("%d",&day);
                                    while (day < 1 || day > 3){
                                    printf("Input hari salah \n");
                                    printf("Hari (Selasa:1,Kamis:3) :\n");
                                    scanf("%d",&day);
                                    }
                                        printf("lab (1-3) \n");
                                        scanf("%d",&lab);
                                            while (lab < 1 || lab > 3){
                                            printf("Input ruangan salah \n");
                                            printf("Lab (1-3) :\n");
                                            scanf("%d",&lab);
                                            }
                                            if (rombongan==3)
                                            {
                                                modul[0][0]=modul[0][0]+1;
                                                    if (modul[0][0] == 6)
                                                {
                                                    printf("Jadwal praktikum rombongan ini telah penuh \n");

                                                }
                                                    else if (lab==1)
                                                {
                                                    strcpy(lab1[week][day],"EB2202-A");//praktikum-rombongan

                                                }
                                                    else if (lab==2)
                                                {
                                                    strcpy(lab2[week][day],"EB2202-A");

                                                }
                                                    else //lab 3
                                                {
                                                    strcpy(lab3[week][day],"EB2202-A");

                                                }
                                            }
                                            else //rombongan B
                                            {
                                                modul[0][1]=modul[0][1]+1;
                                                if (modul[0][1] == 6)
                                                {
                                                printf("Jadwal praktikum rombongan ini telah penuh \n");

                                                }
                                                    else if (lab==1)
                                                {
                                                    strcpy(lab1[week][day],"EB2200-B");//praktikum-rombongan-ruangan lab

                                                }
                                                    else if (lab==2)
                                                {
                                                    strcpy(lab2[week][day],"EB2200-B");

                                                }
                                                    else //lab 3
                                            {
                                                    strcpy(lab3[week][day],"EB2200-B");

                                                }
                                            }
                    }
                       else if (kodeprak == 2)//EL2205
                        {
                            printf("Rombongan (A:3,B:4,C:5,A1:6,A2:7,B1:8,B2:9,C1:10,C2:11) :\n");
                            scanf("%d",&rombongan);
                                while (rombongan < 3 || rombongan > 11){
                                printf("Input rombongan salah \n");
                                printf("Rombongan (A:3,B:4,C:5,A1:6,A2:7,B1:8,B2:9,C1:10,C2:11) :\n");
                                scanf("%d",&rombongan);
                                }
                                    printf("Hari :(0-4) \n");
                                    scanf("%d",&day);
                                        while (day < 0 || day > 4){
                                        printf("Input hari salah \n");
                                        printf("Hari (0-4) :\n");
                                        scanf("%d",&day);
                                        }

                                        if (pmc[week][day]==1 && day != 2){
                                            printf("Input hari bertabrakan dengan EL2208 \n");
                                        }
                                        else {
                                        elek[week][day]=1;
                                        if (rombongan=3)//A1 dan A2
                                                {
                                                    modul[1][0]=modul[1][0]+1;//A1
                                                    modul[1][1]=modul[1][1]+1;//A2
                                                    if (modul[1][0] >= 8||modul[1][1]>=8)
                                                    {
                                                        printf("Jadwal praktikum rombongan ini telah penuh \n");
                                                    }

                                        else {}
                                            printf("lab rombomgan A1(1-3): \n");
                                            scanf("%d",&lab);
                                                while (lab < 1 || lab > 4){
                                                printf("Input ruangan salah \n");
                                                printf("Lab rombomgan A1 (1-3) :\n");
                                                scanf("%d",&lab);
                                                        if (lab==1)
                                                    {
                                                        strcpy(lab1[week][day],"EL2205-A1");//praktikum-rombongan-ruangan lab

                                                    }
                                                        else if (lab==2)
                                                    {
                                                        strcpy(lab2[week][day],"EL2205-A1");

                                                    }
                                                        else //lab 3
                                                    {
                                                        strcpy(lab3[week][day],"EL2205-A1");

                                                    }
                                                }
                                                printf("lab rombomgan A2(1-3): \n");
                                            scanf("%d",&lab);
                                                while (lab < 1 || lab > 3){
                                                printf("Input ruangan salah \n");
                                                printf("Lab rombomgan A2 (1-3) :\n");
                                                scanf("%d",&lab);
                                                }
                                                        if (lab==1)
                                                    {
                                                        strcpy(lab1[week][day],"EL2205-A2");//praktikum-rombongan-ruangan lab

                                                    }
                                                        else if (lab==2)
                                                    {
                                                        strcpy(lab2[week][day],"EL2205-A2");

                                                    }
                                                        else //lab 3
                                                    {
                                                        strcpy(lab3[week][day],"EL2205-A2");

                                                    }
                                                }

                        else if (rombongan=4)//B1 dan B2
                                                {
                                                    modul[1][2]=modul[1][2]+1;//B1
                                                    modul[1][3]=modul[1][3]+1;//B2
                                                    if (modul[1][2] == 8||modul[1][3]==8)
                                                    {
                                                        printf("Jadwal praktikum rombongan ini telah penuh \n");

                                                    }
                                            printf("lab rombomgan B1(1-3): \n");
                                            scanf("%d",&lab);
                                                while (lab < 1 || lab > 3){
                                                printf("Input ruangan salah \n");
                                                printf("Lab rombomgan B1 (1-3) :\n");
                                                scanf("%d",&lab);
                                                        if (lab==1)
                                                    {
                                                        strcpy(lab1[week][day],"EL2205-B1");//praktikum-rombongan-ruangan lab
                                                    }
                                                        else if (lab==2)
                                                    {
                                                        strcpy(lab2[week][day],"EL2205-B1");
                                                    }
                                                        else //lab 3
                                                    {
                                                        strcpy(lab3[week][day],"EL2205-B1");
                                                    }
                                                }
                                                printf("lab rombomgan B2(1-3): \n");
                                            scanf("%d",&lab);
                                                while (lab < 1 || lab > 3){
                                                printf("Input ruangan salah \n");
                                                printf("Lab rombomgan B2 (1-3) :\n");
                                                scanf("%d",&lab);
                                                }
                                                        if (lab==1)
                                                    {
                                                        strcpy(lab1[week][day],"EL2205-B2");//praktikum-rombongan-ruangan lab
                                                    }
                                                        else if (lab==2)
                                                    {
                                                        strcpy(lab2[week][day],"EL2205-B2");
                                                    }
                                                        else //lab 3
                                                    {
                                                        strcpy(lab3[week][day],"EL2205-B2");
                                                    }

                                                }
                        else if (rombongan=5)//C1 dan C2
                                                {
                                                    modul[1][4]=modul[1][4]+1;//C1
                                                    modul[1][5]=modul[1][5]+1;//C2
                                                    if (modul[1][4] == 8||modul[1][5]==8)
                                                    {
                                                        printf("Jadwal praktikum rombongan ini telah penuh \n");

                                                    }

                                            printf("lab rombomgan C1(1-3): \n");
                                            scanf("%d",&lab);
                                                while (lab < 1 || lab > 3){
                                                printf("Input ruangan salah \n");
                                                printf("Lab rombomgan C1 (1-3) :\n");
                                                scanf("%d",&lab);
                                                        if (lab==1)
                                                    {
                                                        strcpy(lab1[week][day],"EL2205-C1");//praktikum-rombongan-ruangan lab
                                                    }
                                                        else if (lab==2)
                                                    {
                                                        strcpy(lab2[week][day],"EL2205-C1");
                                                    }
                                                        else //lab 3
                                                    {
                                                        strcpy(lab3[week][day],"EL2205-C1");
                                                    }
                                                }
                                                printf("lab rombomgan C2(1-3): \n");
                                            scanf("%d",&lab);
                                                while (lab < 1 || lab > 3){
                                                printf("Input ruangan salah \n");
                                                printf("Lab rombomgan C2 (1-3) :\n");
                                                scanf("%d",&lab);
                                                }
                                                        if (lab==1)
                                                    {
                                                        strcpy(lab1[week][day],"EL2205-C2");//praktikum-rombongan-ruangan lab
                                                    }
                                                        else if (lab==2)
                                                    {
                                                        strcpy(lab2[week][day],"EL2205-C2");
                                                    }
                                                        else //lab 3
                                                    {
                                                        strcpy(lab3[week][day],"EL2205-C2");
                                                    }

                                                }
                                   else if (rombongan=6)//A1
                                                {
                                                       modul[1][0]=modul[1][0]+1;//A1
                                                   if (modul[1][0] == 8)
                                                    {
                                                        printf("Jadwal praktikum rombongan ini telah penuh \n");

                                                    }
                                            printf("lab rombomgan A1(1-3): \n");
                                            scanf("%d",&lab);
                                                while (lab < 1 || lab > 3){
                                                printf("Input ruangan salah \n");
                                                printf("Lab rombomgan C1 (1-3) :\n");
                                                scanf("%d",&lab);
                                                        }
                                                        if (lab==1)
                                                    {
                                                        strcpy(lab1[week][day],"EL2205-A1");//praktikum-rombongan-ruangan lab
                                                    }
                                                        else if (lab==2)
                                                    {
                                                        strcpy(lab2[week][day],"EL2205-A1");
                                                    }
                                                        else //lab 3
                                                    {
                                                        strcpy(lab3[week][day],"EL2205-A1");
                                                    }
                                                }
                                       else if (rombongan=7)//A2
                                                {
                                                        modul[1][1]=modul[1][1]+1;//A2
                                                    if (modul[1][1]==8)
                                                    {
                                                        printf("Jadwal praktikum rombongan ini telah penuh \n");

                                                    }
                                            printf("lab rombomgan A2(1-3): \n");
                                            scanf("%d",&lab);
                                                while (lab < 1 || lab > 3){
                                                printf("Input ruangan salah \n");
                                                printf("Lab rombomgan A2 (1-3) :\n");
                                                scanf("%d",&lab);
                                                }
                                                        if (lab==1)
                                                    {
                                                        strcpy(lab1[week][day],"EL2205-A2");//praktikum-rombongan-ruangan lab
                                                    }
                                                        else if (lab==2)
                                                    {
                                                        strcpy(lab2[week][day],"EL2205-A2");
                                                    }
                                                        else //lab 3
                                                    {
                                                        strcpy(lab3[week][day],"EL2205-A2");
                                                    }
                                                }
                               else if (rombongan=8)//B1
                                                {
                                                    modul[1][2]=modul[1][2]+1;//B1
                                                    if (modul[1][2] == 8)
                                                    {
                                                        printf("Jadwal praktikum rombongan ini telah penuh \n");

                                                    }
                                            printf("lab rombomgan B1(1-3): \n");
                                            scanf("%d",&lab);
                                                while (lab < 1 || lab > 3){
                                                printf("Input ruangan salah \n");
                                                printf("Lab rombomgan B1 (1-3) :\n");
                                                scanf("%d",&lab);
                                                }
                                                        if (lab==1)
                                                    {
                                                        strcpy(lab1[week][day],"EL2205-B1");//praktikum-rombongan-ruangan lab
                                                    }
                                                        else if (lab==2)
                                                    {
                                                        strcpy(lab2[week][day],"EL2205-B1");
                                                    }
                                                        else //lab 3
                                                    {
                                                        strcpy(lab3[week][day],"EL2205-B1");
                                                    }
                                                }
                                       else if (rombongan=9)//B2
                                                {
                                                    modul[1][3]=modul[1][3]+1;//B2
                                                    if (modul[1][3]==8)
                                                    {
                                                        printf("Jadwal praktikum rombongan ini telah penuh \n");

                                                    }
                                                printf("lab rombomgan B2(1-3): \n");
                                            scanf("%d",&lab);
                                                while (lab < 1 || lab > 3){
                                                printf("Input ruangan salah \n");
                                                printf("Lab rombomgan B2 (1-3) :\n");
                                                scanf("%d",&lab);
                                                }
                                                        if (lab==1)
                                                    {
                                                        strcpy(lab1[week][day],"EL2205-B2");//praktikum-rombongan-ruangan lab
                                                    }
                                                        else if (lab==2)
                                                    {
                                                        strcpy(lab2[week][day],"EL2205-B2");
                                                    }
                                                        else //lab 3
                                                    {
                                                        strcpy(lab3[week][day],"EL2205-B2");
                                                    }

                                                }
                               else if (rombongan=10)//C1
                                                {
                                                    modul[1][4]=modul[1][4]+1;//C1
                                                    if (modul[1][4] == 8)
                                                    {
                                                        printf("Jadwal praktikum rombongan ini telah penuh \n");

                                                    }
                                            printf("lab rombomgan C1(1-3): \n");
                                            scanf("%d",&lab);
                                                while (lab < 1 || lab > 3){
                                                printf("Input ruangan salah \n");
                                                printf("Lab rombomgan C1 (1-3) :\n");
                                                scanf("%d",&lab);
                                                }
                                                        if (lab==1)
                                                    {
                                                        strcpy(lab1[week][day],"EL2205-C1");//praktikum-rombongan-ruangan lab
                                                    }
                                                        else if (lab==2)
                                                    {
                                                        strcpy(lab2[week][day],"EL2205-C1");
                                                    }
                                                        else //lab 3
                                                    {
                                                        strcpy(lab3[week][day],"EL2205-C1");
                                                    }
                                                }
                               else if (rombongan=11)//C2
                                    {
                                        modul[1][4]=modul[1][4]+1;//C1
                                                    if (modul[1][4] == 8)
                                                    {
                                                        printf("Jadwal praktikum rombongan ini telah penuh \n");

                                                    }
                                                printf("lab rombomgan C2(1-3): \n");
                                                scanf("%d",&lab);
                                                while (lab < 1 || lab > 3){
                                                printf("Input ruangan salah \n");
                                                printf("Lab rombomgan C2 (1-3) :\n");
                                                scanf("%d",&lab);
                                                }
                                                        if (lab==1)
                                                    {
                                                        strcpy(lab1[week][day],"EL2205-C2");//praktikum-rombongan-ruangan lab
                                                    }
                                                        else if (lab=2)
                                                    {
                                                        strcpy(lab2[week][day],"EL2205-C2");
                                                    }
                                                        else //lab 3
                                                    {
                                                        strcpy(lab3[week][day],"EL2205-C2");
                                                    }

                                                }
                                    }
                        }
                      else  //(kodeprak == 1)EL2208
                        {
                            printf("Rombongan (A3:1,B3:2,A:3,B:4,C:5,A1:6,A2:7,B1:8,B2:9) :\n");
                            scanf("%d",&rombongan);
                                while (rombongan < 1 || rombongan > 9){
                                printf("Input rombongan salah \n");
                                printf("Rombongan (A3:1,B3:2,A:3,B:4,C:5,A1:6,A2:7,B1:8,B2:9) :\n");
                                scanf("%d",&rombongan);
                                }
                                    printf("Hari :(Senin-Jumat:0-4) \n");
                                    scanf("%d",&day);
                                        while (day < 0 || day > 4){
                                        printf("Input hari salah \n");
                                        printf("Hari (Senin-Jumat:0-4) :\n");
                                        scanf("%d",&day);
                                        }
                                        while (elek[week][day]==1, day != 2){
                                            printf("Input hari bertabrakan dengan EL2205 \n");

                                        }
                                        pmc[week][day]=1;

                                        if (rombongan=3)//A1 dan A2 dan A3
                                                {
                                                    modul[2][0]=modul[2][0]+1;//A1
                                                    modul[2][1]=modul[2][1]+1;//A2
                                                    modul[2][2]=modul[2][2]+1;//A3
                                                    if (modul[2][0] >= 8||modul[2][1]>=8||modul[2][2]>=8)
                                                    {
                                                        printf("Jadwal praktikum rombongan ini telah penuh \n");

                                                    }
                                            printf("lab rombomgan A1(1-4): \n");
                                            scanf("%d",&lab);
                                                while (lab < 1 || lab > 4){
                                                printf("Input ruangan salah \n");
                                                printf("Lab rombomgan A1 (1-4) :\n");
                                                scanf("%d",&lab);
                                                }
                                                        if (lab==1)
                                                    {
                                                        strcpy(lab1[week][day],"EL2208-A1");//praktikum-rombongan-ruangan lab

                                                    }
                                                        else if (lab==2)
                                                    {
                                                        strcpy(lab2[week][day],"EL2208-A1");

                                                    }
                                                        else if (lab==3)
                                                    {
                                                        strcpy(lab3[week][day],"EL2208-A1");

                                                    }
                                                        else //lab 3
                                                    {
                                                        strcpy(lss[week][day],"EL2208-A1");

                                                    }

                                                printf("lab rombomgan A2(1-4): \n");
                                            scanf("%d",&lab);
                                                while (lab < 1 || lab > 4){
                                                printf("Input ruangan salah \n");
                                                printf("Lab rombomgan A2 (1-4) :\n");
                                                scanf("%d",&lab);
                                                }
                                                        if (lab==1)
                                                    {
                                                        strcpy(lab1[week][day],"EL2208-A2");//praktikum-rombongan

                                                    }
                                                        else if (lab==2)
                                                    {
                                                        strcpy(lab2[week][day],"EL2208-A2");

                                                    }
                                                        else if (lab==3)
                                                    {
                                                        strcpy(lab3[week][day],"EL2208-A2");

                                                    }
                                                        else //lss
                                                    {
                                                        strcpy(lss[week][day],"EL2208-A2");

                                                    }
                                                    printf("lab rombomgan A3(1-4): \n");
                                            scanf("%d",&lab);
                                                while (lab < 1 || lab > 4){
                                                printf("Input ruangan salah \n");
                                                printf("Lab rombomgan A3 (1-4) :\n");
                                                scanf("%d",&lab);
                                                }
                                                        if (lab==1)
                                                    {
                                                        strcpy(lab1[week][day],"EL2208-A3");//praktikum-rombongan

                                                    }
                                                        else if (lab==2)
                                                    {
                                                        strcpy(lab2[week][day],"EL2208-A3");

                                                    }
                                                        else if (lab==3)
                                                    {
                                                        strcpy(lab3[week][day],"EL2208-A3");

                                                    }
                                                        else //lss
                                                    {
                                                        strcpy(lss[week][day],"EL2208-A3");

                                                    }
                                                }
                       else if (rombongan=4)//B1 dan B2 dan B3
                                                {
                                                    modul[2][3]=modul[2][3]+1;//B1
                                                    modul[2][4]=modul[2][4]+1;//B2
                                                    modul[2][5]=modul[2][5]+1;//B2
                                                    if (modul[2][3] >= 10||modul[2][4]>=10||modul[2][5]>=10)
                                                    {
                                                        printf("Jadwal praktikum rombongan ini telah penuh \n");

                                                    }
                                            printf("lab rombomgan B1(1-4): \n");
                                            scanf("%d",&lab);
                                                while (lab < 1 || lab > 4){
                                                printf("Input ruangan salah \n");
                                                printf("Lab rombomgan B1 (1-4) :\n");
                                                scanf("%d",&lab);
                                                        if (lab==1)
                                                    {
                                                        strcpy(lab1[week][day],"EL2208-B1");//praktikum-rombongan

                                                    }
                                                        else if (lab==2)
                                                    {
                                                        strcpy(lab2[week][day],"EL2208-B1");

                                                    }
                                                    else if (lab==3)
                                                    {
                                                        strcpy(lab3[week][day],"EL2208-B1");

                                                    }
                                                        else //lss
                                                    {
                                                        strcpy(lss[week][day],"EL2208-B1");

                                                    }
                                                }
                                                printf("lab rombomgan B2(1-4): \n");
                                            scanf("%d",&lab);
                                                while (lab < 1 || lab > 4){
                                                printf("Input ruangan salah \n");
                                                printf("Lab rombomgan B2 (1-4) :\n");
                                                scanf("%d",&lab);
                                                }
                                                        if (lab==1)
                                                    {
                                                        strcpy(lab1[week][day],"EL2208-B2");//praktikum-rombongan

                                                    }
                                                        else if (lab==2)
                                                    {
                                                        strcpy(lab2[week][day],"EL2208-B2");

                                                    }
                                                        else if (lab==3)
                                                    {
                                                        strcpy(lab3[week][day],"EL2208-B2");

                                                    }
                                                        else //lss
                                                    {
                                                        strcpy(lss[week][day],"EL2208-B2");

                                                    }
                                    printf("lab rombomgan B3(1-4): \n");
                                            scanf("%d",&lab);
                                                while (lab < 1 || lab > 4){
                                                printf("Input ruangan salah \n");
                                                printf("Lab rombomgan B3 (1-4) :\n");
                                                scanf("%d",&lab);
                                                }
                                                        if (lab==1)
                                                    {
                                                        strcpy(lab1[week][day],"EL2208-B3");//praktikum-rombongan

                                                    }
                                                        else if (lab==2)
                                                    {
                                                        strcpy(lab2[week][day],"EL2208-B3");

                                                    }
                                                        else if (lab==3)
                                                    {
                                                        strcpy(lab3[week][day],"EL2208-B3");

                                                    }
                                                        else //lss
                                                    {
                                                        strcpy(lss[week][day],"EL2208-B3");

                                                    }
                                                }
                       else if (rombongan=5)//C
                                                {
                                                    modul[1][6]=modul[1][6]+1;//C
                                                    if (modul[1][6] >= 10)
                                                    {
                                                        printf("Jadwal praktikum rombongan ini telah penuh \n");

                                                    }
                                            printf("lab rombomgan C(1-4): \n");
                                            scanf("%d",&lab);
                                                while (lab < 1 || lab > 4){
                                                printf("Input ruangan salah \n");
                                                printf("Lab rombomgan C (1-4) :\n");
                                                scanf("%d",&lab);
                                                        if (lab==1)
                                                    {
                                                        strcpy(lab1[week][day],"EL2208-C");//praktikum-rombongan-ruangan lab
                                                    }
                                                        else if (lab==2)
                                                    {
                                                        strcpy(lab2[week][day],"EL2208-C");
                                                    }
                                                        else if (lab==3)
                                                    {
                                                        strcpy(lab3[week][day],"EL2208-C");
                                                    }
                                                        else //lss
                                                    {
                                                        strcpy(lab3[week][day],"EL2208-C");
                                                    }
                                                }


                                                }
                                   else if (rombongan=6)//A1
                                                {
                                                    modul[2][0]=modul[2][0]+1;//A1
                                                   if (modul[2][0] == 10)
                                                    {
                                                        printf("Jadwal praktikum rombongan ini telah penuh \n");

                                                    }
                                            printf("lab rombomgan A1(1-4): \n");
                                            scanf("%d",&lab);
                                                while (lab < 1 || lab > 4){
                                                printf("Input ruangan salah \n");
                                                printf("Lab rombomgan A1 (1-4) :\n");
                                                scanf("%d",&lab);
                                                        }
                                                 if (lab==1)
                                                    {
                                                        strcpy(lab1[week][day],"EL2208-A1");//praktikum-rombongan-ruangan lab
                                                    }
                                                        else if (lab==2)
                                                    {
                                                        strcpy(lab2[week][day],"EL2208-A1");
                                                    }
                                                         else if (lab==3)
                                                    {
                                                        strcpy(lab3[week][day],"EL2208-A1");
                                                    }
                                                        else //lss
                                                    {
                                                        strcpy(lss[week][day],"EL2208-A1");
                                                    }
                                                }
                                      else if (rombongan=7)//A2
                                                {
                                                    modul[2][1]=modul[2][1]+1;//A2
                                                    if (modul[2][1]>=10)
                                                    {
                                                        printf("Jadwal praktikum rombongan ini telah penuh \n");

                                                    }
                                            printf("lab rombomgan A2(1-4): \n");
                                            scanf("%d",&lab);
                                                while (lab < 1 || lab > 4){
                                                printf("Input ruangan salah \n");
                                                printf("Lab rombomgan A2 (1-4) :\n");
                                                scanf("%d",&lab);
                                                }
                                                        if (lab==1)
                                                    {
                                                        strcpy(lab1[week][day],"EL2208-A2");//praktikum-rombongan-ruangan lab
                                                    }
                                                        else if (lab==2)
                                                    {
                                                        strcpy(lab2[week][day],"EL2208-A2");
                                                    }
                                                        else if (lab==3)
                                                    {
                                                        strcpy(lab3[week][day],"EL2208-A2");
                                                    }
                                                        else //lss
                                                    {
                                                        strcpy(lss[week][day],"EL2208-A2");
                                                    }
                                                }
                               else if (rombongan=8)//B1
                                                {
                                                    modul[2][3]=modul[2][3]+1;//B1
                                                    if (modul[2][3] >= 10)
                                                    {
                                                        printf("Jadwal praktikum rombongan ini telah penuh \n");

                                                    }
                                            printf("lab rombomgan B1(1-4): \n");
                                            scanf("%d",&lab);
                                                while (lab < 1 || lab > 4){
                                                printf("Input ruangan salah \n");
                                                printf("Lab rombomgan B1 (1-4) :\n");
                                                scanf("%d",&lab);
                                                }
                                                        if (lab==1)
                                                    {
                                                        strcpy(lab1[week][day],"EL2208-B1");//praktikum-rombongan
                                                    }
                                                        else if (lab==2)
                                                    {
                                                        strcpy(lab2[week][day],"EL2208-B1");
                                                    }
                                                        else if (lab==3)
                                                    {
                                                        strcpy(lab3[week][day],"EL2208-B1");
                                                    }
                                                        else //lss
                                                    {
                                                        strcpy(lss[week][day],"EL2208-B1");
                                                    }
                                                }
                                       else if (rombongan=9)//B2
                                                {
                                                    modul[2][4]=modul[2][4]+1;//B2
                                                    if (modul[2][4]>=10)
                                                    {
                                                        printf("Jadwal praktikum rombongan ini telah penuh \n");

                                                    }
                                                printf("lab rombomgan B2(1-4): \n");
                                            scanf("%d",&lab);
                                                while (lab < 1 || lab > 4){
                                                printf("Input ruangan salah \n");
                                                printf("Lab rombomgan B2 (1-4) :\n");
                                                scanf("%d",&lab);
                                                }
                                                        if (lab==1)
                                                    {
                                                        strcpy(lab1[week][day],"EL2208-B2");//praktikum-rombongan-ruangan lab
                                                    }
                                                        else if (lab==2)
                                                    {
                                                        strcpy(lab2[week][day],"EL2208-B2");
                                                    }
                                                        else if (lab==3)
                                                    {
                                                        strcpy(lab2[week][day],"EL2208-B2");
                                                    }
                                                        else //lss
                                                    {
                                                        strcpy(lss[week][day],"EL2208-B2");
                                                    }

                                                }
                               else if (rombongan=1)//A3
                                                {
                                                    modul[2][2]=modul[2][2]+1;//A3
                                                   if (modul[2][2] == 10)
                                                    {
                                                        printf("Jadwal praktikum rombongan ini telah penuh \n");

                                                    }
                                            printf("lab rombomgan A3(1-4): \n");
                                            scanf("%d",&lab);
                                                while (lab < 1 || lab > 4){
                                                printf("Input ruangan salah \n");
                                                printf("Lab rombomgan A3 (1-4) :\n");
                                                scanf("%d",&lab);
                                                        }
                                                        if (lab==1)
                                                    {
                                                        strcpy(lab1[week][day],"EL2208-A3");//praktikum-rombongan-ruangan lab
                                                    }
                                                        else if (lab==2)
                                                    {
                                                        strcpy(lab2[week][day],"EL2208-A3");
                                                    }
                                                        else if (lab==3)
                                                    {
                                                        strcpy(lab3[week][day],"EL2208-A3");
                                                    }
                                                        else //lss
                                                    {
                                                        strcpy(lss[week][day],"EL2208-A3");
                                                    }
                                                }
                               else if (rombongan=2)//B3
                                    {
                                        modul[2][5]=modul[2][5]+1;//B3
                                                    if (modul[2][5]>=10)
                                                    {
                                                        printf("Jadwal praktikum rombongan ini telah penuh \n");
                                                    }
                                                printf("lab rombomgan B3(1-4): \n");
                                            scanf("%d",&lab);
                                                while (lab < 1 || lab > 4){
                                                printf("Input ruangan salah \n");
                                                printf("Lab rombomgan B3 (1-4) :\n");
                                                scanf("%d",&lab);
                                                }
                                                        if (lab==1)
                                                    {
                                                        strcpy(lab1[week][day],"EL2208-B3");//praktikum-rombongan-ruangan lab
                                                    }
                                                        else if (lab==2)
                                                    {
                                                        strcpy(lab2[week][day],"EL2208-B3");
                                                    }
                                                        else if (lab==3)
                                                    {
                                                        strcpy(lab2[week][day],"EL2208-B3");
                                                    }
                                                        else //lss
                                                    {
                                                        strcpy(lss[week][day],"EL2208-B3");
                                                    }

                                                }

                        }
                }



}
}


void showA(char Alab1[][5][2], char Alab2[][5][2], char Alab3[][5][2],
	char Alss[][5][2])
{
	int week, day;
	printf("|--------------------------------------------------------------------|\n");
	printf("|Ruang Praktikum |    LAB1    |    LAB2    |    LAB3    |    LSS     |\n");
	printf("|----------------|------------|------------|------------|------------|\n");
	printf("|Minggu |  Hari  |------------|------------|------------|------------|\n");
	printf("|-------|--------|------------|------------|------------|------------|\n");
	for (week = 3; week <= 15; week++){

		for (day = 0; day <= 4; day ++){
            printf("|   %d   |", week);
			switch (day){

				case 0 : printf(" Senin  |");
                    break;
				case 1 : printf(" Selasa |");
                    break;
				case 2 : printf(" Rabu   |");
                    break;
				case 3 : printf(" Kamis  |");
                    break;
				case 4 : printf(" Jumat  |");
                    break;
				default :printf(" Invalid|");

            }
            printLab(Alab1[week][day]);
            printLab(Alab2[week][day]);
            printLab(Alab3[week][day]);
            printLab(Alss[week][day]);
            printf("\n");

		}
		printf("|--------------------------------------------------------------------|\n");
	}
}

int fillA(char lab1[][5][10],char lab2[][5][10],char lab3[][5][10],
	char lss[][5][10], char *Alab1[][5][2],char *Alab2[][5][2],
	char *Alab3[][5][2], char *Alss[][5][2])
{
	unsigned int bool_kelas, is_penuh = 0;
	int week = 0, day = -1, n_asist;
	char asist = 'x', arr_asist[2], room[10], arr_kelas[10], arr_day[10];
	while (1){
		printf("Pilih Asisten: ");
		scanf("%c", &asist);
		//kondisi keluar
		if ((asist == 'Q' || asist == 'q')){
			break;
		//validasi asisten
		} else if (('A' <= asist) && (asist <= 'N')){
			//validasi minggu
			while ((week < 3) || (week > 15)){
                printf("Masukan minggu harus 3-15\n");
				printf("Minggu: ");
				scanf("%d", &week);

			}
			//validasi hari
			while (day == -1){
				printf("Hari: ");
				scanf("%s", arr_day);
				if (strcmp(arr_day, "Senin") == 0){
					day = 0;
				} else if (strcmp(arr_day, "Selasa") == 0){
					day = 1;
				} else if (strcmp(arr_day, "Rabu") == 0){
					day = 2;
				} else if (strcmp(arr_day, "Kamis") == 0){
					day = 3;
				} else if (strcmp(arr_day, "Jumat") == 0){
					day = 4;
				} else {
					printf("Masukan hari harus Senin sampai Jumat");
				}
			}
			//validasi ruang
			while (1){
				printf("Ruang: ");
				scanf("%s", room);
				if (strcmp(room, "LAB1") == 0){
					strcpy(arr_kelas, lab1[week][day]);
					strcpy(arr_asist, Alab1[week][day]);
					break;
				} else if (strcmp(room, "LAB2") == 0){
					strcpy(arr_kelas, lab2[week][day]);
					strcpy(arr_asist, Alab2[week][day]);
					break;
				} else if (strcmp(room, "LAB3") == 0){
					strcpy(arr_kelas, lab3[week][day]);
					strcpy(arr_asist, Alab3[week][day]);
					break;
				} else if (strcmp(room, "LSS") == 0){
					strcpy(arr_kelas, lss[week][day]);
					strcpy(arr_asist, Alss[week][day]);
					break;
				}
			}
			//pengecekan variabel asist
			if (asist == 'A' || asist == 'a'){
					if (strcmp(arr_kelas, "EL2205") == 0){
						if (day != 2) {
							bool_kelas = 1;
						} else {
							printf("Asisten praktikum Amir tidak tersedia pada hari Rabu\n");
						}
					} else {
						printf("Asisten praktikum Amir hanya tersedia pada EL2205\n");
					}
			} else if (asist == 'B' || asist == 'b'){
					if (strcmp(arr_kelas, "EL2205") == 0){
						if (day != 0) {
							bool_kelas = 1;
						} else {
							printf("Asisten praktikum Budi tidak tersedia pada hari Senin\n");
						}
					} else {
						printf("Asisten praktikum Budi hanya tersedia pada EL2205\n");
					}
            } else if (asist == 'C' || asist == 'c'){
					if (strcmp(arr_kelas, "EL2205") == 0){
						if ((day != 1) && (day != 2)) {
							bool_kelas = 1;
						} else {
							printf("Asisten praktikum Cici tidak tersedia pada hari Selasa dan Rabu\n");
						}
					} else {
						printf("Asisten praktikum Cici hanya tersedia pada EL2205\n");
					}
			} else if (asist == 'D' || asist == 'd'){
					if (strcmp(arr_kelas, "EL2205") == 0){
						if ((day != 0) && (day != 2)) {
							bool_kelas = 1;
						} else {
							printf("Asisten praktikum Doni tidak tersedia pada hari Senin dan Rabu\n");
						}
					} else {
						printf("Asisten praktikum Doni hanya tersedia pada EL2205\n");
					}
			} else if (asist == 'E' || asist == 'e'){
					if ((strcmp(arr_kelas, "EL2205") && strcmp(arr_kelas, "EL2208")) == 0){
						bool_kelas = 1;
					} else {
						printf("Asisten praktikum Endang hanya tersedia pada EL2205 dan EL2208\n");
					}
			} else if (asist == 'F' || asist == 'f'){
					if (strcmp(arr_kelas, "EL2205") == 0){
						if (day != 1) {
							bool_kelas = 1;
						} else {
							printf("Asisten praktikum Fadel tidak tersedia pada hari Selasa\n");
						}
					} else {
						printf("Asisten praktikum Fadel hanya tersedia pada EL2205\n");
					}
			} else if (asist == 'G' || asist == 'g'){
					if ((strcmp(arr_kelas, "EL2205") && strcmp(arr_kelas, "EB2200")) == 0){
						if (day != 3) {
							bool_kelas = 1;
						} else {
							printf("Asisten praktikum Gilang tidak tersedia pada hari Kamis\n");
						}
					} else {
						printf("Asisten praktikum Gilang hanya tersedia pada EL2205 dan EB2200\n");
					}
			} else if (asist == 'H' || asist == 'h'){
					if (strcmp(arr_kelas, "EL2208") == 0){
						if (day != 3) {
							bool_kelas = 1;
						} else {
							printf("Asisten praktikum Hero tidak tersedia pada hari Kamis\n");
						}
					} else {
						printf("Asisten praktikum Hero hanya tersedia pada EL2208\n");
					}
			} else if (asist == 'I' || asist == 'i'){
					if ((strcmp(arr_kelas, "EL2205") && strcmp(arr_kelas, "EL2208") && strcmp(arr_kelas, "EB2200")) == 0){
						if (day != 2) {
							bool_kelas = 1;
						} else {
							printf("Asisten praktikum Intan tidak tersedia pada hari Rabu\n");
						}
					} else {
						printf("Input ruang salah\n");
					}
			} else if (asist == 'J' || asist == 'j'){
					if (strcmp(arr_kelas, "EL2208") == 0){
						if (day != 4) {
							bool_kelas = 1;
						} else {
							printf("Asisten praktikum Joko tidak tersedia pada hari Jumat\n");
						}
					} else {
						printf("Asisten praktikum Joko hanya tersedia pada EL2208\n");
					}
			} else if (asist == 'K' || asist == 'k'){
					if ((strcmp(arr_kelas, "EL2208") && strcmp(arr_kelas, "EB2200")) == 0){
						if (day != 4) {
							bool_kelas = 1;
						} else {
							printf("Asisten praktikum Kiki tidak tersedia pada hari Jumat\n");
						}
					} else {
						printf("Asisten praktikum Kiki hanya tersedia pada EL2208 dan EB2200\n");
					}
			} else if (asist == 'L' || asist == 'l'){
					if (strcmp(arr_kelas, "EL2208") == 0){
						bool_kelas = 1;
					} else {
						printf("Asisten praktikum Luis hanya tersedia pada EL2208\n");
					}
			} else if (asist == 'M' || asist == 'm'){
					if (strcmp(arr_kelas, "EL2208") == 0){
						if ((day != 2) && (day != 3)) {
							bool_kelas = 1;
						} else {
							printf("Asisten praktikum Mini tidak tersedia pada hari Rabu dan Kamis\n");
						}
					} else {
						printf("Asisten praktikum Mini hanya tersedia pada EL2208\n");
					}
			} else if (asist == 'N' || asist == 'n'){
					if ((strcmp(arr_kelas, "EL2208") && strcmp(arr_kelas, "EB2200")) == 0){
						if (day != 1) {
							bool_kelas = 1;
						} else {
							printf("Asisten praktikum Nina tidak tersedia pada hari Selasa\n");
						}
					} else {
						printf("Asisten praktikum Nina hanya tersedia pada EL2208 dan EB2200\n");
					}
			} else {
					printf("Failure in checking 'asist'\n");
			}
			//assignment ke array alab
			if (bool_kelas == 1){
				if (arr_asist[0] == ""){
					n_asist = 0;
				} else if (arr_asist[1] == ""){
					n_asist = 1;
				} else {
					is_penuh = 1;
					printf("Lab sudah penuh diisi dua asisten\n");
				}
				if (is_penuh == 0){
					if (strcmp(room, "LAB1") == 0){
						Alab1[week][day][n_asist] = asist;
					} else if (strcmp(room, "LAB2") == 0){
						Alab2[week][day][n_asist] = asist;
					} else if (strcmp(room, "LAB3") == 0){
						Alab3[week][day][n_asist] = asist;
					} else if (strcmp(room, "LSS") == 0){
						Alss[week][day][n_asist] = asist;
					}
				}
			}
		} else {
			printf("Masukan asisten harus A-N\n");
		}
	}
}

//void autoS(){}
//void autoA(){}

void reduceS(char x[][5][10],int w, int d,int modul[][10]){
// fungsi reduce mengurangi jumlah modul yang telah dilakukan
//[0][0] = EB2200-A ; [0][1] = EB2200-B
//[1][0] = EL2205-A1; [1][1] = EL2205-A2; [1][2] = EL2205-B1;
//[1][3] = EL2205-B2; [1][4] = EL2205-C1; [1][5] = EL2205-C2
//[2][0] = EL2208-A1; [2][1] = EL2208-A2; [2][2] = EL2208-A1
//[2][3] = EL2208-B1; [2][4] = EL2208-B2; [2][5] = EL2208-B3; [2][6] = EL2208-C
	if(strcmp(x[w][d], "EB2200-A")){
		modul[0][0] = modul[0][0] - 1;
	}

	else if(strcmp(x[w][d], "EB2200-B")){
		modul[0][1] = modul[0][1] -1;
	}
	else if(strcmp(x[w][d], "EL2205-A1")){
		modul[1][0] = modul[1][0] -1;
	}
	else if(strcmp(x[w][d], "EL2205-A2")){
		modul[1][1] = modul[1][1] -1;
	}
	else if(strcmp(x[w][d], "EL2205-B1")){
		modul[1][2] = modul[1][2] -1;
	}
	else if(strcmp(x[w][d], "EL2205-B2")){
		modul[1][3] = modul[1][3] -1;
	}
	else if(strcmp(x[w][d], "EL2205-C1")){
		modul[1][4] = modul[1][4] -1;
	}
	else if(strcmp(x[w][d], "EL2205-C2")){
		modul[1][5] = modul[1][5] -1;
	}
	else if(strcmp(x[w][d], "EL2208-A1")){
		modul[2][0] = modul[2][0] -1;
	}
	else if(strcmp(x[w][d], "EL2208-A2")){
		modul[2][1] = modul[2][1] -1;
	}
	else if(strcmp(x[w][d], "EL2208-A3")){
		modul[2][2] = modul[2][2] -1;
	}
	else if(strcmp(x[w][d], "EL2208-B1")){
		modul[2][3] = modul[2][3] -1;
	}
	else if(strcmp(x[w][d], "EL2208-B2")){
		modul[2][4] = modul[2][4] -1;
	}
	else if(strcmp(x[w][d], "EL2208-B3")){
		modul[2][5] = modul[2][5] -1;
	}
	else if(strcmp(x[w][d], "EL2208-C")){
		modul[2][6] = modul[2][6] -1;
	}
	else{

	}
}

void rule(char lab1[][5][10],char lab2[][5][10],char lab3[][5][10],char lss[][5][10],char Alab1[][5][2],char Alab2[][5][2],char Alab3[][5][2],char Alss[][5][2],char filerule[],int modul[][10]){
   FILE * fp;
	int d[100];
	int w[100];
	int i = 0;
	int j = 0;
	int k = 0;
	char day[100];
	int week;

	fp = fopen (filerule, "r");
	printf("Hari libur pada : \n('Minggu ke' 'Hari')\n");
	for(i=0;i<100;i++){
		fscanf(fp, "%d %s", &w[i],day);
		printf("%d %s \n" ,w[i],day);

		if(!feof(fp)){
			//senin
			if(strcmp(day, "Senin") == 0){
				d[i] = 0;
			}
			//selasa
			else if(strcmp(day, "Selasa") == 0){
				d[i] = 1;
			}
			//rabu
			else if(strcmp(day, "Rabu") == 0){
				d[i] = 2;
			}
			//kamis
			else if(strcmp(day, "Kamis") == 0){
				d[i] = 3;
			}
			//jumat
			else{
				d[i] = 4;
			}
		k=k+1;
		}
		else {

			break ;
		}

	}

	//hapus data pada tanggal libur
	for(j=0;j<k;j++){
		//kurangi modul
			reduceS(lab1,w[j],d[j],modul);
			reduceS(lab2,w[j],d[j],modul);
			reduceS(lab3,w[j],d[j],modul);
			reduceS(lss,w[j],d[j],modul);
			//hapus isi

			strcpy(lab1[w[j]][d[j]],"");
			strcpy(lab2[w[j]][d[j]],"");
			strcpy(lab3[w[j]][d[j]],"");
			strcpy(lss[w[j]][d[j]],"");

			/*strcpy(Alab1[w[j]][d[j]][1],"");
			strcpy(Alab2[w[j]][d[j]][1],"");
			strcpy(Alab3[w[j]][d[j]][1],"");
			strcpy(Alss[w[j]][d[j]][1],"");
			strcpy(Alab1[w[j]][d[j]][2],"");
			strcpy(Alab2[w[j]][d[j]][2],"");
			strcpy(Alab3[w[j]][d[j]][2],"");
			strcpy(Alss[w[j]][d[j]][2],"");
	*/
		}

		fclose(fp);
}

void save(char lab1[][5][10],char lab2[][5][10],char lab3[][5][10],char lss[][5][10],char Alab1[][5][2],char Alab2[][5][2],char Alab3[][5][2],char Alss[][5][2],char fileschd[],char fileasst[]){
	//menyimpan array lab1,lab2...lss ke file jadwal, dan Alab1, Alab2, .... Alss ke file asisten. file dengan format csv. format mengikuti panduan praktikum. untuk memudahkan
	//isi cell dipepet ke kiri saja. tempat kosong diisi dengan spasi.ss
	    int w,d;
    FILE *fp1;
	fp1 = fopen(fileschd, "w");
	for (w=1;16;w++)
    {
        for (d=0;4;d++)
        {
            fprintf(fp1, "%s,%s,%s",lab1[w][d],lab2[w][d],lab3[w][d],lss[w][d]);
        }
    }
	fclose(fp1);

	FILE *fp2;
	fp2 = fopen(fileasst, "w");
	for (w=1;16;w++)
    {
        for (d=0;4;d++)
        {
            fprintf(fp2, "%s,%s,%s",Alab1[w][d],Alab2[w][d],Alab3[w][d],Alss[w][d]);
        }
    }
	fclose(fp2);
}

