#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, char const *argv[])
{
	if(argc > 1)
	{
		// Processing argc and argv
		if(strstr(argv[1], "--help"))
		{
            printf("\n[*] Input:\n    ~~~~~~\n\n\tNONE\n\n[*] Output:\n    ~~~~~~~\n\n\t\"pp.data\"\n\n[*] Use this program to create iPP chain, which is in LAMMPS data file format. Output from this program can be used as input in LAMMPS script with minimal modification.\n\n");
			exit(1);
		}
		else
		{
			printf("\nError:\n~~~~~~\n\n\tUnknown command passed. Type '--help' for more information or run the executable directly\n\n");
			exit(1);
		}
	}

//	CHANGE ATOM ID, BOND ID, ANGLE ID AND DIHEDRAL ID TO CHANGE THE SERIAL NUMBERS FOR ATOMS, BONDS, ANGLES AND DIHEDRALS. IDEALLY, ATOM ID IS 4, BOND ID IS 4, ANGLE ID IS 4 AND DIHEDRAL ID IS 1.

	int dop, natoms, nanglestotal, atomid=4;
	int nbonds, bondid=4, bondatom;
	int angleid=4, angleatom;
	int dihedralatom, dihedralid=1, ndihedrals, loopdih=0;
	int f1, f2, f3, f4;
	float x1=2.0156, y1=3.2574, z1=2.0, x2=2.0, y2=3.0, z2=2.0, x3=2.0, y3=2.0156, z3=3.2574;

	FILE *print;
	print=fopen("pp.data","w");

	bondatom=atomid+1;
	angleatom=atomid+1;
	dihedralatom=atomid;

	printf("Enter the number of repeating monomers in the required polymer chain\n");
	scanf("%d", &dop);

	fprintf(print, "Created by you v1.8.1 on today, this month, this year, current time.\n\n");

	natoms=dop*3+1;
	fprintf(print, "\t%d\tatoms\n", natoms);

	nbonds=dop*3;
	fprintf(print, "\t%d\tbonds\n", nbonds);

	nanglestotal=(dop*4)-1;
	fprintf(print, "\t%d\tangles\n", nanglestotal);

	ndihedrals=(dop-1)*4;
	fprintf(print, "\t%d\tdihedrals\n", ndihedrals);
	loopdih=(((dop-2)*2)+2)/2;
	printf("\n\nloopdih is %d\n\n", loopdih);

	fprintf(print, "\t0\timpropers\n");

	fprintf(print, "\n\t3 atom types\n\t2 bond types\n\t3 angle types\n\t1 dihedral types\n\t0 improper types\n\n\t-x\t+x\txlo xhi\n\t-y\t+y\tylo yhi\n\t-z\t+z\tzlo zhi\n\nMasses\n\n\t1\t13.0907\t#CG311 CH\n\t2\t14.1707\t#CG321 CH2\n\t3\t15.2507\t#CG331 CH3\n\nAtoms\n\n");

	fprintf(print, "\t%d\t0\t3\t%f\t%f\t%f\t#CG331\n", atomid-3, x1, y1, z1);
	fprintf(print, "\t%d\t0\t1\t%f\t%f\t%f\t#CG311\n", atomid-2, x2, y2, z2);
	fprintf(print, "\t%d\t0\t3\t%f\t%f\t%f\t#CG331\n", atomid-1, x3, y3, z3);

	for(f1=0;f1<dop-1;f1++)
	{
		x1=x1+2.5147;
//		y1=y1+2.5147;
//		z1=z1+2.5147;
		x2=x2+2.5147;
//		y2=y2+2.5147;
//		z2=z2+2.5147;
		x3=x3+2.5147;
//		y3=y3+2.5147;
//		z3=z3+2.5147;

		fprintf(print, "\t%d\t0\t2\t%f\t%f\t%f\t#CG321\n", atomid, x1, y1, z1);
		fprintf(print, "\t%d\t0\t1\t%f\t%f\t%f\t#CG311\n", atomid+1, x2, y2, z2);
		fprintf(print, "\t%d\t0\t3\t%f\t%f\t%f\t#CG331\n", atomid+2, x3, y3, z3);
		atomid=atomid+3;

	}

		x1=x1+2.5147;
		y1=y1+2.5147;
		z1=z1+2.5147;
		fprintf(print, "\t%d\t0\t3\t%f\t%f\t%f\t#CG321\n", atomid, x1, y1, z1);

	fprintf(print, "\nBonds\n\n");

		fprintf(print, "\t%d\t1\t%d\t%d\t#CG311 - CG331\n", bondid-3, bondatom-4, bondatom-3);
		fprintf(print, "\t%d\t1\t%d\t%d\t#CG311 - CG331\n", bondid-2, bondatom-3, bondatom-2);
		fprintf(print, "\t%d\t2\t%d\t%d\t#CG311 - CG321\n", bondid-1, bondatom-3, bondatom-1);

	for(f2=0; f2<dop-1;f2++)
	{

		fprintf(print, "\t%d\t2\t%d\t%d\t#CG321 - CG311\n", bondid, bondatom-1, bondatom);
		fprintf(print, "\t%d\t1\t%d\t%d\t#CG311 - CG331\n", bondid+1, bondatom, bondatom+1);
		fprintf(print, "\t%d\t2\t%d\t%d\t#CG311 - CG321\n", bondid+2, bondatom, bondatom+2);
		bondid=bondid+3;
		bondatom=bondatom+3;
	}

	fprintf(print, "\nAngles\n\n");

		fprintf(print, "\t%d\t2\t%d\t%d\t%d\t#CG331 - CG311 - CG331\n", angleid-3, angleatom-4, angleatom-3, angleatom-2);
		fprintf(print, "\t%d\t1\t%d\t%d\t%d\t#CG331 - CG311 - CG321\n", angleid-2, angleatom-4, angleatom-3, angleatom-1);
		fprintf(print, "\t%d\t1\t%d\t%d\t%d\t#CG331 - CG311 - CG321\n", angleid-1, angleatom-2, angleatom-3, angleatom-1);

	for(f3=0; f3<dop-2; f3++)
	{

		fprintf(print, "\t%d\t1\t%d\t%d\t%d\t#CG311 - CG321 - CG311\n", angleid, angleatom-3, angleatom-1, angleatom);
		fprintf(print, "\t%d\t3\t%d\t%d\t%d\t#CG321 - CG311 - CG331\n", angleid+1, angleatom-1, angleatom, angleatom+1);
		fprintf(print, "\t%d\t1\t%d\t%d\t%d\t#CG321 - CG311 - CG321\n", angleid+2, angleatom-1, angleatom, angleatom+2);
		fprintf(print, "\t%d\t3\t%d\t%d\t%d\t#CG331 - CG311 - CG321\n", angleid+3, angleatom+1, angleatom, angleatom+2);

	angleid=angleid+4;
	angleatom=angleatom+3;

	}

		fprintf(print, "\t%d\t1\t%d\t%d\t%d\t#CG311 - CG321 - CG311\n", angleid, angleatom-3, angleatom-1, angleatom);
		fprintf(print, "\t%d\t3\t%d\t%d\t%d\t#CG321 - CG311 - CG331\n", angleid+1, angleatom-1, angleatom, angleatom+1);
		fprintf(print, "\t%d\t3\t%d\t%d\t%d\t#CG321 - CG311 - CG321\n", angleid+2, angleatom-1, angleatom, angleatom+2);
		fprintf(print, "\t%d\t2\t%d\t%d\t%d\t#CG331 - CG311 - CG331\n", angleid+3, angleatom+1, angleatom, angleatom+2);

	fprintf(print, "\nDihedrals\n\n");

	for(f4=0; f4<loopdih; f4++)
	{

		fprintf(print, "\t%d\t1\t%d\t%d\t%d\t%d\t# CG311 (CG331) CG311 CG321 CG311\n", dihedralid, dihedralatom-3, dihedralatom-2, dihedralatom, dihedralatom+1);
		fprintf(print, "\t%d\t1\t%d\t%d\t%d\t%d\t# CG311 (CG331) CG311 CG321 CG311\n", dihedralid+1, dihedralatom-1, dihedralatom-2, dihedralatom, dihedralatom+1);
		fprintf(print, "\t%d\t1\t%d\t%d\t%d\t%d\t# CG311 CG321 CG311 CG331\n", dihedralid+2, dihedralatom-2, dihedralatom, dihedralatom+1, dihedralatom+2);
		fprintf(print, "\t%d\t1\t%d\t%d\t%d\t%d\t# CG311 CG321 CG311 CG321\n", dihedralid+3, dihedralatom-2, dihedralatom, dihedralatom+1, dihedralatom+3);

	dihedralid=dihedralid+4;
	dihedralatom=dihedralatom+3;

	}

	fclose(print);

	return(0);

}
