/*****************************************************************************************************************************/
/**															    **/
/**															    **/
/**															    **/
/**			## This program is a hack.  It's brute force.  It's horrible.                			    **/
/**			## It doesn't use Artificial Intelligence.  It doesn't use Virtual Reality. 			    **/
/**			## It's not perl.  It's not python.  It probably won't work unchanged on    			    **/
/**			## the "other" thousands of unices.  But it worksforme.                     			    **/
/**															    **/
/**															    **/
/**						  				Quoted from run-mozilla.sh		    **/
/**															    **/
/**															    **/
/*****************************************************************************************************************************/


/*****************************************************************************************************************************/
/**															    **/
/**	Version 0.2 :	- Make it run as filter										    **/
/**			- Add -rev keyword 										    **/
/**			- If two .ps files are defined, assume that they contain two ps images whose upper and lower	    **/
/**			  triangles must be merged.									    **/
/**			- Variance-covariance calculus added								    **/
/**			- NR eigenvalue & eigenvector functions added							    **/
/**			- Projection of fluctuations on eigenvectors.							    **/
/**			- Projection of trajectory on eigenvectors.							    **/
/**															    **/
/**	Version 0.3 :	- Keyword "-sort" added										    **/
/**			- By default carma will now write only Ca atoms in the trajectory file. If all other atoms are	    **/
/**			  needed, they will simply be copied as is (with the "-noCA" flag)				    **/
/**			- Got rid of proprietary eigen routines. The LAPACK library is now the default.			    **/
/**															    **/
/**	Version 0.4 : 	- Try to detect DCD wrong endianess from header info						    **/
/**			- Allow the possibility of using numerical recipes' eigenroutines ...				    **/
/**			- "-use" flag added to allow re-using previously calculated eigenvalues and vectors		    **/
/**															    **/
/**	Version 0.5 :	- Atom type selection keyword added (-atomid keyword)    					    **/
/**			- segid selection keyword added (-segid)							    **/
/**			- 'fit' added											    **/
/**			- 'ref' added											    **/
/**			- 'arti' added											    **/
/**															    **/
/**	Version 0.6 :	- atmid "ALLID" possibility added to allow selection of all atoms				    **/
/**			- '-index' added to select atom indeces for fitting						    **/
/**															    **/
/**	Version 0.7 :	- Mass-weighted covariance matrix 	:   flag -mass						    **/
/**			- Entropy calculation based on PC 	:   flag -temp						    **/
/**			- Sigmoidal weighting scheme 		:   flag -sigm						    **/
/**			- Distribution map calculation 		:   flag -map						    **/
/**			- Exorcised nasty bug writing nonsense DCDs when the -first flag is given			    **/
/**			- Fixed a numerical problem with bestfit() for the case of two equal roots			    **/
/**			- On the fly distribution map calculation : flag -fmap						    **/
/**			- Fixed a bug with -first (when -first was pointing to an offset of more than 2GBytes)		    **/
/**			- Primitive graphics capabilities 	:   flag -g						    **/
/**								    flag -loop						    **/
/**								    flag -cpk						    **/
/**								    flag -trace						    **/
/**								    flag -sp						    **/
/**															    **/
/**	Version 0.8 :	- Can now read and write unit cell information from DCD files 					    **/
/**			- Increased the default line thickness for backbone trace					    **/
/**			- W key writes (in pause mode) a ppm image file of the current graphics view			    **/
/**			- B key enters pause mode with PBC images displayed						    **/
/**			- Plus and minus keys increase/decrease frame step during viewing				    **/
/**			- When called as 'carma my.psf my.dcd' will go straight into trajectory viewing mode		    **/
/**			- Keywords added : '-distance' and '-torsion'							    **/
/**			- Keyword '-reposition'										    **/
/**			- Keyword '-nofit'										    **/
/**			- Entropy calcs revisited ...									    **/
/**															    **/
/**															    **/
/**	Version 0.9 :	- Flag '-col'  added for producing colour postscript	 					    **/
/**			- Flag '-Rg'   added for mass-weighted radius of gyration calculation				    **/
/**			- Flag '-dPCA' added for dihedral PCA								    **/
/**			- Arguments to flag '-proj' modified to match '-dPCA' (and to produce DeltaG plots)		    **/
/**			- Flag '-surf' added for calculation of surface area estimate					    **/
/**			- Primitive cluster analysis (actually peak-picking on 3D PCA map) implemented			    **/
/**			- When calculating covariance matrix with '-dot', write-out average PDB & fluctuations		    **/
/**			- When calculating covariance matrix with '-dot', write-out rmsd from average			    **/
/**			- Flag '-pdb' added for exporting PDB files							    **/
/**															    **/
/**	Version 1.0 :	- Don't abort with empty lines in the 'fit.index' file						    **/
/**			- Flag '-shannon' added for calculation of configurational entropy of 3D PC distribution	    **/
/**			- Bug-fixing for cluster analysis for the case of very few frames 				    **/
/**			- Incremental rmsd (between successive frames) implemented via second argument to '-ref'	    **/
/**			- Added '-CRYST' flag to calculate distribution map in the crystallographic frame		    **/
/**			- Added rudimentary support for PSF files with the EXT extension				    **/
/**			- Fixed an issue with the unit cell flag in the DCD file header for CHARMM-produced DCD files	    **/
/**			- When the '-w' flag is given, carma will produce a pseudo-PSF file which specifies the selected    **/
/**			  atoms (and can only be used with carma, sorry).						    **/
/**			- Modified '-distance' arguments so that many distances can be determined simultaneously (for NOEs) **/
/**															    **/
/**	Version 1.1 :	- Fix enumeration of dPCA torsion angles for forcefields other than CHARMM			    **/
/**			- Write CCP4 (na4) map with the 3D landscape from PCA, flag '-3d'				    **/
/**			- Fix bug with atomic masses when non-CHARMM 							    **/
/**			- Incorporate bending angles patch contributed by Ian Grant <Ian.Grant@ruhr-uni-bochum.de>	    **/
/**			- Changed the binning intervals for cluster analysis.						    **/
/**			- When writing PDBs and unit cell is known, add a CRYST1 card at the PDB header.		    **/
/**			- Automatic determination of RMSD cutoff for cluster analysis implemented			    **/
/**			- Flag "-cross" added to allow calculation of RMSD matrices 					    **/
/**			- Flag "-chi1" added to include the chi1 angles in dPCA analysis				    **/
/**			- Modified '-torsion' arguments so that many angles can be determined simultaneously (for Jcoupl)   **/
/**															    **/
/**	Version 1.2 :	- Mass-weighted pair distance distribution added (flag '-pddf')		       			    **/
/**			- Attempt to run stride automatically through carma (flag '-stride')				    **/
/**			- In graphics mode 'W' key writes a PDB file in addtion to PPM.					    **/
/**			- Use '-super' when preparing average structure to also prepare a superposition PDB + RMSFs	    **/
/**			- Fraction of native contacts (vs. first frame) added. Keyword '-Qfraction <distance> <separation>' **/
/**			- Flag "-bend" can also read a series of triplets from a file.  				    **/
/**			- Couple of arrays made static to fix issues with windoze's '-fstack-check' ... ;-/		    **/
/**			- Fix a small bug in cluster analysis. Should have fewer 'boo's' ....				    **/
/**															    **/
/**															    **/
/**															    **/
/**															    **/
/**															    **/
/*****************************************************************************************************************************/


#define		LAPACK	1
#undef		NR

#ifdef WINDOWS
#define 	M_PI           	3.14159265358979323846
#define 	M_E             2.7182818284590452354 
#define		NR		1
#undef 		LAPACK
#endif
	

#if defined (LAPACK) && defined (NR)
#undef          NR
#endif

#ifdef GRA
#include <Ygl.h>
#define         BG              0
#define         FG              1
#define         AXES            5
#define         ZERO            4
#define         POS             4
#define         NEG             7
#define         AUTH            6
#define         AXESTR          7
#define		WINSIZE		600
#define		LINEW		3
#endif

#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>                     

#define		NO			0
#define		YES			1
#define         min(a,b,c)      	((a)<=(b) && (a)<=(c) ? (a) : ((b)<=(c) ? (b) : (c)))
#define         max(a,b,c)      	((a)>=(b) && (a)>=(c) ? (a) : ((b)>=(c) ? (b) : (c)))
#define         max2(a,b)       	((a) >= (b) ? (a) : (b))
#define         min2(a,b)       	((a) <= (b) ? (a) : (b))
#define         FREE_ARG        	char*
#define         NR_END          	1
#define		_UNROLL			1
#define         nearint(a)      	((a) < 0.0 ? (int)(a-0.50) : (int)(a+0.50))

#ifdef WINDOWS

#define         random          	rand
#define         srandom         	srand
#define         MAXRAND         	((float)(RAND_MAX)+1.0)

#else

#define         MAXRAND         	((float)(INT_MAX)+1.0)

#endif

#define         getrand         	((float)(random())/MAXRAND)


#define HBAR            (double)(1.05457168e-34)    
#define KBOL            (double)(1.3806505e-23)
#define HOVERK          (double)(7.6382233e-12)
#define AMU             (double)(1.660538860e-27)
#define AVOGADRO        (double)(6.02214150e23)
#define	CONST1		(double)(48.50867485)		/* (HBAR^2 / Kb) / (AMU*1e-20) */
#define	CONST2		(double)(0.020614869)		/* (AMU*1e-20) / (HBAR^2 / Kb) */
#define DGCONST		(double)(0.00198716728333)


#define	  ATOM_TYPES	163

char atom_names[ATOM_TYPES][5] = {
				"C   ", "CA  ", "CAL ", "CC  ", "CD  ", 
				"CE1 ", "CE2 ", "CEL1", "CEL2", "CES ", 
				"CL  ", "CLA ", "CM  ", "CN1 ", "CN1A", 
				"CN1T", "CN2 ", "CN3 ", "CN3A", "CN3B", 
				"CN3C", "CN3D", "CN3T", "CN4 ", "CN5 ", 
				"CN5G", "CN7 ", "CN7B", "CN7C", "CN7D", 
				"CN8 ", "CN8B", "CN9 ", "CNA ", "CNA2", 
				"CNE1", "CNE2", "CP1 ", "CP2 ", "CP3 ", 
				"CPA ", "CPB ", "CPH1", "CPH1", "CPH2", 
				"CPH2", "CPM ", "CPT ", "CS  ", "CT1 ", 
				"CT2 ", "CT3 ", "CTL1", "CTL2", "CTL3", 
				"CTL5", "CY  ", "DUM ", "FE  ", "FN1 ", 
				"FNA ", "H   ", "HA  ", "HAL1", "HAL2", 
				"HAL3", "HB  ", "HC  ", "HCL ", "HE  ", 
				"HE1 ", "HE2 ", "HEL1", "HEL2", "HL  ", 
				"HN1 ", "HN2 ", "HN3 ", "HN3B", "HN3C", 
				"HN4 ", "HN5 ", "HN6 ", "HN7 ", "HN8 ", 
				"HN9 ", "HNE1", "HNE2", "HNP ", "HOL ", 
				"HP  ", "HR1 ", "HR1 ", "HR2 ", "HR3 ", 
				"HR3 ", "HS  ", "HT  ", "HT  ", "MG  ", 
				"N   ", "NC2 ", "NE  ", "NH1 ", "NH2 ", 
				"NH3 ", "NH3L", "NN1 ", "NN1C", "NN2 ", 
				"NN2B", "NN2C", "NN2G", "NN2U", "NN3 ", 
				"NN3A", "NN3G", "NN3I", "NN4 ", "NN5 ", 
				"NN6 ", "NP  ", "NPH ", "NR1 ", "NR1 ", 
				"NR2 ", "NR2 ", "NR3 ", "NTL ", "NY  ", 
				"O   ", "O2L ", "OB  ", "OBL ", "OC  ", 
				"OCL ", "OH1 ", "OHL ", "OM  ", "ON1 ", 
				"ON1C", "ON2 ", "ON2b", "ON3 ", "ON4 ", 
				"ON5 ", "ON6 ", "ON6B", "OS  ", "OSL ", 
				"OT  ", "OT  ", "P   ", "P2  ", "PL  ", 
				"POT ", "S   ", "SL  ", "SM  ", "SOD ", 
				"SS  ", "ZN  ", "AR  "
							};

float	atom_masses[ATOM_TYPES] = {
				12.01100, 12.01100, 40.08000, 12.01100, 12.01100,
				12.01100, 12.01100, 12.01100, 12.01100,132.90000,
				12.01100, 35.45000, 12.01100, 12.01100, 12.01100,
				12.01100, 12.01100, 12.01100, 12.01100, 12.01100,
				12.01100, 12.01100, 12.01100, 12.01100, 12.01100,
				12.01100, 12.01100, 12.01100, 12.01100, 12.01100,
				12.01100, 12.01100, 12.01100, 12.01100, 12.01100,
				12.01100, 12.01100, 12.01100, 12.01100, 12.01100,
				12.01100, 12.01100, 12.01100, 12.01100, 12.01100,
				12.01100, 12.01100, 12.01100, 12.01100, 12.01100,
				12.01100, 12.01100, 12.01100, 12.01100, 12.01100,
				12.01100, 12.01100,  0.00000, 55.84700, 18.99840,
				18.99840,  1.00800,  1.00800,  1.00800,  1.00800,
				 1.00800,  1.00800,  1.00800,  1.00800,  4.00260,
				 1.00800,  1.00800,  1.00800,  1.00800,  1.00800,
				 1.00800,  1.00800,  1.00800,  1.00800,  1.00800,
				 1.00800,  1.00800,  1.00800,  1.00800,  1.00800,
				 1.00800,  1.00800,  1.00800,  1.00800,  1.00800,
				 1.00800,  1.00800,  1.00800,  1.00800,  1.00800,
				 1.00800,  1.00800,  1.00800,  1.00800, 24.30500,
				14.00700, 14.00700, 20.17970, 14.00700, 14.00700,
				14.00700, 14.00700, 14.00700, 14.00700, 14.00700,
				14.00700, 14.00700, 14.00700, 14.00700, 14.00700,
				14.00700, 14.00700, 14.00700, 14.00700, 14.00700,
				14.00700, 14.00700, 14.00700, 14.00700, 14.00700,
				14.00700, 14.00700, 14.00700, 14.00700, 14.00700,
				15.99940, 15.99940, 15.99940, 15.99940, 15.99940,
				15.99940, 15.99940, 15.99940, 15.99940, 15.99940,
				15.99940, 15.99940, 15.99940, 15.99940, 15.99940,
				15.99940, 15.99940, 15.99940, 15.99940, 15.99940,
				15.99940, 15.99940, 30.97400, 30.97400, 30.97400,
				39.10200, 32.06000, 32.06000, 32.06000, 22.98977,
				32.06000, 65.37000, 39.94800
							};


#ifdef GRA

#define CARBONC 	2
#define CALCIUMC 	3
#define CHLORC 		4
#define HYDROGENC 	5
#define NITROGENC 	6
#define OXYGENC 	7
#define PHOSPHOC 	8
#define SULPHC 		9
#define IRONC 		10
#define SODC 		11
#define MAGNC 		12
#define ZINCC 		13
#define OTHERC 		15

int	atom_colors[ATOM_TYPES] = {
					CARBONC,   CARBONC,   CALCIUMC,  CARBONC,   CARBONC,
					CARBONC,   CARBONC,   CARBONC,   CARBONC,   OTHERC,
					CARBONC,   CHLORC,    CARBONC,   CARBONC,   CARBONC,
					CARBONC,   CARBONC,   CARBONC,   CARBONC,   CARBONC,
					CARBONC,   CARBONC,   CARBONC,   CARBONC,   CARBONC,
					CARBONC,   CARBONC,   CARBONC,   CARBONC,   CARBONC,
					CARBONC,   CARBONC,   CARBONC,   CARBONC,   CARBONC,
					CARBONC,   CARBONC,   CARBONC,   CARBONC,   CARBONC,
					CARBONC,   CARBONC,   CARBONC,   CARBONC,   CARBONC,
					CARBONC,   CARBONC,   CARBONC,   CARBONC,   CARBONC,
					CARBONC,   CARBONC,   CARBONC,   CARBONC,   CARBONC,
					CARBONC,   CARBONC,   OTHERC,    IRONC,     OTHERC,
					OTHERC,    HYDROGENC, HYDROGENC, HYDROGENC, HYDROGENC,
					HYDROGENC, HYDROGENC, HYDROGENC, HYDROGENC, OTHERC,
					HYDROGENC, HYDROGENC, HYDROGENC, HYDROGENC, HYDROGENC,
					HYDROGENC, HYDROGENC, HYDROGENC, HYDROGENC, HYDROGENC,
					HYDROGENC, HYDROGENC, HYDROGENC, HYDROGENC, HYDROGENC,
					HYDROGENC, HYDROGENC, HYDROGENC, HYDROGENC, HYDROGENC,
					HYDROGENC, HYDROGENC, HYDROGENC, HYDROGENC, HYDROGENC,
					HYDROGENC, HYDROGENC, HYDROGENC, HYDROGENC, MAGNC,
					NITROGENC, NITROGENC, OTHERC,    NITROGENC, NITROGENC,
					NITROGENC, NITROGENC, NITROGENC, NITROGENC, NITROGENC,
					NITROGENC, NITROGENC, NITROGENC, NITROGENC, NITROGENC,
					NITROGENC, NITROGENC, NITROGENC, NITROGENC, NITROGENC,
					NITROGENC, NITROGENC, NITROGENC, NITROGENC, NITROGENC,
					NITROGENC, NITROGENC, NITROGENC, NITROGENC, NITROGENC,
					OXYGENC,   OXYGENC,   OXYGENC,   OXYGENC,   OXYGENC,
					OXYGENC,   OXYGENC,   OXYGENC,   OXYGENC,   OXYGENC,
					OXYGENC,   OXYGENC,   OXYGENC,   OXYGENC,   OXYGENC,
					OXYGENC,   OXYGENC,   OXYGENC,   OXYGENC,   OXYGENC,
					OXYGENC,   OXYGENC,   PHOSPHOC,  PHOSPHOC,  PHOSPHOC,
					OTHERC,    SULPHC,    SULPHC,    SULPHC,    SODC,
					SULPHC,    ZINCC
							};

#endif

#ifdef LAPACK

extern	void ssyev_();
int	EIGEN = NO;
void	eigen();
float	*eigenvalues;
float	**eigenvectors;
int	eigendim;
int	EIGENFIRST   = -1;
int	EIGENLAST    = -1;
int	EIGENSTEP    = -1;
int	EIGENFIRST_W = -1;
int	EIGENLAST_W  = -1;
int	EIGENSTEP_W  = -1;
float	EIGENPLAY_FIRST = 0.0;
float	EIGENPLAY_LAST  = 0.0;
int	EIGENPLAY  	= -1;
int	USE_LAST	= NO;	

#endif


#ifdef NR

void	jacobi();
void 	eigsrt();
#define	ROTATE(a,i,j,k,l) g=a[i][j];h=a[k][l];a[i][j]=g-s*(h+g*tau);a[k][l]=h+s*(g-h*tau);
int	EIGEN = NO;
void	eigen();
static float sqrarg;
#define SIGN(a,b) ((b) >= 0.0 ? fabs(a) : -fabs(a))
#define SQRNR(a) ((sqrarg=(a)) == 0.0 ? 0.0 : sqrarg*sqrarg)
void	tred2();
void	tqli();

float	*eigenvalues;
float	**eigenvectors;
int	eigendim;
int	EIGENFIRST   = -1;
int	EIGENLAST    = -1;
int	EIGENSTEP    = -1;
int	EIGENFIRST_W = -1;
int	EIGENLAST_W  = -1;
int	EIGENSTEP_W  = -1;
float	EIGENPLAY_FIRST = 0.0;
float	EIGENPLAY_LAST  = 0.0;
int	EIGENPLAY  	= -1;
int	USE_LAST	= NO;

#endif



typedef float rotate_t[3][3];
typedef float xlate_t[3];

#define FABS(a) ((a) > 0 ? (a) : (-a))
#define SQRTABS(a) ((a) > 0 ? sqrt(a) : sqrt(-a))
#define fsqrt(a) sqrt(a)
#define SQR(a) ((a)*(a))
#define DSQR(a) ((double)(a)*(double)(a))
#define CUBE(a) ((a)*(a)*(a))
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))


/* torsion calculation stolen from RDPARM/PTRAJ */
double	torsion();
#define VOP_3D_COORDS_CROSS_PRODUCT(TX,TY,TZ,UX,UY,UZ,VX,VY,VZ) \
  TX = (UY * VZ) - (UZ * VY); \
  TY = (UZ * VX) - (UX * VZ); \
  TZ = (UX * VY) - (UY * VX)

/* bending angle calculation modelled on torsion */
double bendangle();


float  bestfit();
double vsumsqr(const float v[], unsigned int n);
double vsumby3(const float v[], unsigned int n);
double dvdot(const double a[], const double b[], unsigned int n);
double vdotby3(const float a[], const float b[], unsigned int n);


void    free_vector();
void    free_matrix();
void    free_f3tensor();
void    free_int3tensor();
float   **matrix( long nrl, long nrh, long ncl, long nch );
float   ***f3tensor(long nrl, long nrh, long ncl, long nch, long ndl, long ndh );
unsigned short int	***int3tensor(long nrl, long nrh, long ncl, long nch, long ndl, long ndh );
void    nrerror( char error_text[]);
float   *vector();
void    myexit();

int	get_pdb_coords();
int	read_psf();
void 	wps();
void 	wps_color();
void    getcol( float val, int *r, int *g, int *b );    
void    build_CAs();
void    write_CAs();
void    write_CAs2();
float	Dist();
void 	filter();
void	mergeps();
void	sortdcd();
int	build_torsions();
int	build_torsions_with_chi();
void	cluster( int bins, int tframes, float limit );
void 	erase_peak();
void    tona4();
void 	write_map();



#define	MAX_NOF_CAS	300000
#define MAX_NOF_TORS	40000
#define MAX_NOF_BACK	80000

float	CAs[MAX_NOF_CAS][3];		/* thirty thousand 'residues' should be enough for most purposes */
int	posCAs[MAX_NOF_CAS];		/* this will hold the atom numbers of the CAs in .dcd files */
int	realCAs[MAX_NOF_CAS];		/* For TRICK */
int	reposition[MAX_NOF_CAS];
int	limitCAs[MAX_NOF_CAS];
int	realCAscount = 0;
int	colorindex[MAX_NOF_CAS];
float	masses[MAX_NOF_CAS];
char	str_segname[MAX_NOF_CAS][5];
int	str_resid[MAX_NOF_CAS];
char	str_resname[MAX_NOF_CAS][5];
char	str_atname[MAX_NOF_CAS][5];



int	tetraplets[MAX_NOF_TORS][4];	/* Set of tetraplets of atom indeces for dPCA */
char	backbone[MAX_NOF_BACK][11];	/* Backbone atoms for dPCA torsion selection */
int	nof_torsions;

int	nofCAs;
float	*dcd_frame;
float	*wdcd_frame;
float	**D1; 			/* Data matrices */
float	**D2;
float	**D3;
float	**DG;
float	**Dref;
float	***CLUSTER;
float	gmin = 0.0;		/* Plotting min max */
float	gmax = 10.0;
float	*pD1;			/* Pointers to data arrays (for sequencial access) */
float	*pD2;
float	*pD3;
int	nofPSFatoms = 0;
int	totentered;
char	pscomment[300] = "";

int	HAVE_PDB = 0;
int	HAVE_DCD = 0;
int	HAVE_PSF = 0;
int	HAVE_MAX = NO;
int	HAVE_MIN = NO;
int	FIRST = -1;
int	LAST = -1;
int	STEP = 1;
int	FIND_RMS = NO;
int	REVERSE = NO;
float	MAX_RMSD = -1.0;
int	VERBOSE = NO;
int	WRITE_DATA = NO;
int	SIGMOIDAL = NO;
float	LAMBDA = 4.0;
int	FILTER = NO;
int	HAVE_PS = -1;
int	FIND_COV = NO;
int	USE_DOT = NO;
int	NORMALISE = NO;
int	WRITE_CAS = YES;
char	ATOMID[300];
char	SEGID[300];
int	ALL_ATID = NO;
int	HEAVY = NO;
int	HAVE_SEGID = NO;
int	DO_FIT = NO;
int	ARTIFICIAL = NO;
int	ART_EIGEN = -1;
int	ART_FRAMES = -1;
int	REFERENCE = 1;
int	HAVE_INDEX = NO ;
int	MASSES = NO;
int	ENTROPY = NO;
float	Temp = -1.0;
int	CALC_MAP = NO;
int	FAST_MAP = NO;
float	Xmin = 0.0;
float	Xmax = 0.0;
float	Ymin = 0.0;
float	Ymax = 0.0;
float	Zmin = 0.0;
float	Zmax = 0.0;
float	Grid = 0.250;
int	PLAYING = NO;
int	HAVE_CELL = NO;
int	CELL_OFFSET = 0;
double	cell_a;
double	cell_gamma;
double	cell_b;
double	cell_beta;
double	cell_alpha;
double	cell_c;
int	DISTFIRST = -1;
int	DISTSECOND = -1;
int	TORSFIRST = -1;
int	TORSSECOND = -1;
int	TORSTHIRD = -1;
int	TORSFOURTH = -1;
int 	BENDFIRST = -1;
int 	BENDSECOND = -1;
int 	BENDTHIRD = -1;
int	REPOSITION = NO;
int	NOFIT = NO;
int	COLOUR = NO;

float	  RED_1 = 0.0;
float	GREEN_1 = 0.0;
float	 BLUE_1 = 0.1;

float	  RED_2 = 0.0;
float	GREEN_2 = 0.3;
float	 BLUE_2 = 0.8;

float	  RED_3 = 1.0;
float	GREEN_3 = 1.0;
float	 BLUE_3 = 0.0;

float	  RED_4 = 0.8;
float	GREEN_4 = 0.3;
float	 BLUE_4 = 0.0;

float	  RED_5 = 0.1;
float	GREEN_5 = 0.0;
float	 BLUE_5 = 0.0;

int	GYRATION = NO;
int	DPCA = NO;
int	DG_PLOTS = 0;
float	DGTEMP = 300.0;
int	ASA = NO;
float	CLU_RMS = -1.0;
FILE	*rms_aver;
int	WRITE_PDB = NO;
int	WRITE_SUPER = NO;
int	STRIDE = NO;
float	DGLEN = -1.0;
int	SHANNON = NO;
int	REF_STEP = NO;
int	HAVE_DISTANCE_FILE = NO;
int	HAVE_TORSION_FILE = NO;
int	HAVE_BEND_FILE = NO;
char	DIST_NAME[1000];
char	TORS_NAME[1000];
char	BEND_NAME[1000];
int	MAKE_3D = NO;
int	CROSSDCD = NO;
int	CHI1 = NO;

double	MAP_VARIANCE;
double	MAP_AVER;
double	MAP_RMSD;
int	GRID_POINTS;

int	QFRACTION = NO;
float	Q_CUTOFF  = 8.0;
int	Q_SEPARATION = 2;
int	HAVE_REF = NO;
FILE	*q_file;
int	tot_for_qfraction;
int	tot_for_qsfraction;
int	tot_for_sfraction;


/* Density map in crystallographic frame */
double	f2o_11, f2o_12, f2o_13, f2o_14;
double	f2o_21, f2o_22, f2o_23, f2o_24;
double	f2o_31, f2o_32, f2o_33, f2o_34;
int	cryst_x, cryst_y, cryst_z;
int	CRYSTALLOGRAPHIC_FRAME = NO;


/* For pair distance distribution */
#define	PDDF_STEP	0.25  /* In Angstrom */
int	PDDF = NO;
float	pddf[1000];


#ifdef GRA
long	winid;
int	GRAPHICS = NO;
int	YGL_INIT = NO;
float	GRABOX = 50.0;
int	STEREO = NO;
float	CROSS = 5.0;
float	XOFFSET = 0.0;
float	YOFFSET = 0.0;
int	GRADIENT = NO;
int	GRA_VIEW = 3;
int	LOOP = NO;
int	CPK  = NO;
int	TRICK = NO;
int	TRICK_FIRST = -1;
int	TRICK_LAST = -1;
void	static_view();
void 	copyCAs();
double 	omega, phi, kappa;
double 	domega, dphi, dkappa;
float	cCAs[MAX_NOF_CAS][3];
float	ccCAs[MAX_NOF_CAS][3];
int	now_playing = NO;
int	PACKING = NO;
int	PACKING_FIRST = NO;
int	AUTOGRA = NO;
double  orthom00;
double  orthom10;
double  orthom20;
double  orthom01;
double  orthom11;
double  orthom21;
double  orthom02;
double  orthom12;
double  orthom22;
void	calc_ortho();
#endif
char	framestring[100];

unsigned int	headerframes;


#ifndef WINDOWS
time_t	start_timer;
time_t	end_timer;
#endif




int main(argc,argv)
int  	argc;
char	*argv[];
{
	int	i,k;
	float	max, min;
	int	dcd;
	char	dcd_head[92];
	char	dcd_head2[16];
	char	title[81];
	char	filename[300];
	char	frameno[30];
	int	frame;
	int	firstframe;
	int	tempr;
	off_t	start;
	off_t	start_ref;
	off_t	afterheader;
	int	entered;
	int	psindex[10];
	float	v1, v2;
	char	junk[300];
	float	junkf;
	float	temp;

	unsigned int	nofatoms;
	unsigned int	auint;
	unsigned int	bytes_per_set;
	unsigned int	wbytes_per_set;


#ifndef WINDOWS
	start_timer = time(NULL);
#endif


/*****************************************************************************************************************************/
/**   Prelude                                                                                                               **/
/*****************************************************************************************************************************/


	
						/* Use the program as a filter to prepare a postscript file containing */
						/* a grayscale representation of a nxn matrix given from stdin */
						
	for ( i=1 ; i < argc ; i++)
		if ( strcmp( argv[i], "-") == 0 )
			FILTER = YES;

						/* If two postscript files are defined on input, then these must be */
						/* merged about the diagonal */	
	k = 0;
	for ( i=1 ; i < argc ; i++)
		if ( strncasecmp( &argv[i][ strlen( argv[i]) - 3], ".PS", 3) == 0 )
			psindex[k++] = i;
	if ( k == 2 )
		mergeps( argv[psindex[0]], argv[psindex[1]] );
	if ( k > 0 )
		{
			printf("\033[31m\033[1mA lone postscript file as input ? Abort.\033[0m\n");
			myexit( 1 );
					}
					
	
		
	
         
	for ( i=1 ; i < argc ; i++)
	{	
	if ( strncasecmp( &argv[i][ strlen( argv[i]) - 4], ".PDB", 4) == 0 )
		{
			HAVE_PDB = i;
			if ( sscanf( argv[i], "%f", &junkf ) == 1 )
				printf("\033[33mWarning: PDB filename looks like a number.\033[0m\n");
		}
	if ( strncasecmp( &argv[i][ strlen( argv[i]) - 4], ".DCD", 4) == 0 )
		{
			HAVE_DCD = i;
			if ( sscanf( argv[i], "%f", &junkf ) == 1 )
				printf("\033[33mWarning: DCD filename looks like a number.\033[0m\n");   
		}                          
	if ( strncasecmp( &argv[i][ strlen( argv[i]) - 4], ".PSF", 4) == 0 )
		{
			HAVE_PSF = i;
			if ( sscanf( argv[i], "%f", &junkf ) == 1 )
				printf("\033[33mWarning: PSF filename looks like a number.\033[0m\n");   

					
			
			if ( strlen( argv[i]) == 24 && strncmp(  &argv[i][ strlen( argv[i]) - 24], "carma.selected_atoms.psf", 24) == 0 )
			{
			for ( k=1 ; k < argc ; k++)
				if ( strncasecmp( &argv[k][0], "-W", 2) == 0 )
					{
					printf("\033[31m\033[1m\nRefusing to overwrite the input PSF file (carma.selected_atoms.psf). Please rename.\033[0m\n\n");
					myexit(1);
					}
			}
			
		}                         
	}


	for ( i=1 ; i < argc ; i++)
		if ( strncasecmp( argv[i], "-SO", 3) == 0 )
			{
				if ( HAVE_DCD > 0 )
					sortdcd( argv[HAVE_DCD], argv[i+1] );
				else
					{
					printf("\033[31m\033[1m\"-sort\" without a DCD file specification ?\033[0m\n");
					myexit(1);
					}
			}
		else if ( strncasecmp( argv[i], "-V", 2) == 0 )
				VERBOSE = YES;		
					
#ifdef GRA

	if ( argc == 3 && HAVE_PDB == 0 && HAVE_DCD > 0 && HAVE_PSF > 0 )					
		{
			AUTOGRA = YES;
			GRABOX = 100.0;
			CROSS = GRABOX / 60.0;
                        GRAPHICS = YES;
			TRICK = YES;
			ALL_ATID = YES;
		}

#endif					


/*****************************************************************************************************************************/
/**	Info														    **/
/*****************************************************************************************************************************/

	if ( argc == 1 || (HAVE_PDB == 0 && HAVE_DCD == 0 && HAVE_PSF == 0 && FILTER==NO))
		{

		printf("\n\033[37m\033[1mcarma v.1.2\033[4;37m____________________________________________________________________\033[0m\n");

		printf("\033[32m\nOptions : \033[0m\n");

		printf("    -verb       : Be more talkative.\n");
		printf("    -cov        : Calculate variance-covariance matrix.\n");
		printf("    -rms        : Calculate average and rms distance maps.\n");
		printf("    -pddf       : Calculate mass-weighted pair distance distribution.\n");
		printf("    -first <i>  : First DCD frame to use.\n");
		printf("    -last  <i>  : Last  DCD frame to use.\n");
		printf("    -step  <i>  : Use every <step>th DCD frame.\n");
		printf("    -max   <f>  : Largest CA-CA distance to plot.\n");
		printf("    -min   <f>  : Smallest CA-CA distance to plot.\n");
		printf("    -col [<15f>]: Produce colour postscript.\n");
		printf("    -rev        : Reverse contrast of plot (vs default).\n");
		printf("    -mrms  <f>  : Largest CA-CA rms deviation to plot.\n");
		printf("    -sigm  <f>  : Apply sigmoidal weighting before writing out.\n");
		printf("    -write      : Create a file containing the numerical results.\n");
		printf("    -mass       : Use mass-weighting for the covariance matrix.\n");
		printf("    -dot        : Calculate the dot-product derived covariance matrix.\n");
		printf("    -norm       : Normalise the variance-covariance matrix (cross correlation).\n");
		printf("    -rg         : Calculate mass-weighted radius of gyration.\n");
		printf("    -fit        : Remove global rotations-translations from DCD frames.\n");
		printf("    -cross      : Calculate RMSD matrix.\n");
		printf("    -ref        : Reference frame for fitting.\n");
		printf("    -index      : Select atoms for fitting using an index file (fit.index).\n");
		printf("    -pdb        : Write PDB files for all selected atoms & frames.\n");
		printf("    -stride     : In conjuction with -pdb, attempt to run STRIDE on the PDBs.\n");
		printf("    -surf       : Calculate surface area metric for selected segid(s).\n");
		printf("    -super      : Prepare a superposition of structures used to calculate average.\n");
		printf("    -Qfract <fi>: Calculate fraction of native contacts vs first frame.\n");
		printf("    -dist <2i>|s: Calculate distance between given atoms\n");
		printf("    -tors <4i>|s: Calculate torsion angle between given atoms\n");
		printf("    -bend <3i>|s: Calculate bending angle between given atoms\n");
		printf("    -map  <7f>  : Produce distribution map from DCD in xplor-cns format.\n");
		printf("    -fmap <7f>  : On the fly calculation of distribution map from DCD.\n");
		printf("    -atmid <s>  : Atom-name-based atom selection.\n");
		printf("    -segid <s>  : Segment-identifier-based atom selection (dcd-psf only).\n\n");

#ifdef GRA
		printf("    -gra   <f>  : Enable primitive graphics display.\n");
		printf("    -cpk        : Colour atoms (dots) according to type.\n");
		printf("    -loop       : Loop graphics display of trajectory.\n");
		printf("    -trace      : Draw a Ca- or P- trace.\n");
		printf("    -sp         : Colour atoms (dots) using a color gradient.\n\n");
#endif

#if defined (LAPACK) || defined (NR)
		printf("    -dpca <2if> : Dihedral angle (phi-psi) principal component analysis.\n");
		printf("    -chi1       : Include chi1 angles in dihedral PCA\n");
		printf("    -eigen      : Calculate eigenvectors and values of covariance matrices.\n");
		printf("    -dgwidth <f>: Scale PCA-based DeltaG plots to a width of <f> Angstrom.\n");
		printf("    -use        : Use eigenvectors and values from a previous run of carma.\n");
		printf("    -proj <2if> : Calculate projection of fluctuations on selected eigenvectors\n");
		printf("    -out  <3i>  : Calculate projection of trajectory on selected eigenvectors.\n");
		printf("    -play <i2f> : Construct a smooth trajectory for the selected eigenvector.\n");
		printf("    -art  <2i>  : Use eigenvectors to construct an atrificial trajectory.\n");
		printf("    -noCAs      : Transfer all non CA atoms (as is) to outputed trajectory.\n");
		printf("    -temp <f>   : Calculate Sho using the given temperature value.\n");
		printf("    -3D         : Write PCA-derived 3D landscape (in CCP4-NA4 format).\n");

#endif

		printf("\n\033[4;37m____________________________\033[0m\033[37m Helper applications \033[0m\033[4;37m______________________________\033[0m\n\n");

		printf("\033[32mcarma -col -\033[0m\n");
		printf("\tRead [n*n] values from stdin, and make a color postscript bitmap.\n");

		printf("\033[32mcarma <first.ps> <second.ps>\033[0m\n");
		printf("\tRead two carma-made postscript files and make a composite image.\n");

		printf("\033[32mcarma -sort <frame_order.list> <my.dcd>\033[0m\n");
		printf("\tReorder frames in DCD file to match the order in <frame_order.list>.\n");

		printf("\033[4;37m_______________________________________________________________________________\033[0m\n\n");
					
		myexit(0);
		}
	
	

	if ( FILTER==NO && HAVE_PDB != NO && ( HAVE_DCD != NO || HAVE_PSF != NO ))
		{
			printf("\033[31m\033[1mToo many input files. You should either define a PDB alone,\nor a DCD plus its PSF.\033[0m\n");
			myexit(1);
		}

	SEGID[0] = 0;
	ATOMID[0] = 0;

/*****************************************************************************************************************************/
/**	Input parsing													    **/
/*****************************************************************************************************************************/

	for ( i=1 ; i < argc ; i++)
	{	
	if ( strncasecmp( argv[i], "-FIR", 4) == 0 )
		{
			if ( HAVE_PDB != NO )
				printf("\033[31m\033[1mFrame specification for a .pdb file ? Ignored.\033[0m\n");
				
                        if ( sscanf( argv[i+1], "%d", &FIRST ) != 1 )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-first\".\033[0m\n");
					myexit( 1 );
                                                        }
			i++;
                        if ( FIRST <= 0 )
                        	{
                        		printf("\033[31m\033[1mFrame numbers must be greater than zero.\033[0m\n");
                        		myexit(1);
                        				}
                        
								}
	else if ( strncasecmp( argv[i], "-LA", 3) == 0 )
		{
			if ( HAVE_PDB != NO )
				printf("\033[31m\033[1mFrame specification for a .pdb file ? Ignored.\033[0m\n");
				
                        if ( sscanf( argv[i+1], "%d", &LAST ) != 1 )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-last\".\033[0m\n");
					myexit( 1 );
                                                        }
			i++;
                        if ( LAST <= 0 )
                        	{
                        		printf("\033[31m\033[1mFrame numbers must be greater than zero.\033[0m\n");
                        		myexit(1);
                        				}
                        
								}
	else if ( strncasecmp( argv[i], "-AT", 3) == 0 )
		{
			char	inter[6] = "     ";

                        if ( sscanf( argv[i+1], "%s", &junk[0] ) != 1 )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-atomid\".\033[0m\n");
					myexit( 1 );
                                                        }
                        i++;
                        
                        if ( strlen( argv[i] ) > 5 )
                        	{
                        		printf("\033[31m\033[1mAtom specification error : string (%s) too long.\033[0m\n", argv[i]);
                        		myexit(1);
                        				}
                        if ( strncasecmp( argv[i], "ALLID", 5 ) == 0 )
				ALL_ATID = YES;
                        if ( strncasecmp( argv[i], "HEAVY", 5 ) == 0 )
				HEAVY = YES;
			else if ( strlen( argv[i] ) < 5 )
				strncpy( &inter[1], argv[i], strlen(argv[i]) );
                        else
				strncpy( &inter[0], argv[i], strlen(argv[i]) );

			strcat( &ATOMID[0], &inter[0] );
								}
	else if ( strncasecmp( argv[i], "-SE", 3) == 0 )
		{
			char 	inter[6] = "     ";
			int	m;

			if ( HAVE_PDB == YES || HAVE_PSF == NO )
				{
				printf("\033[31m\033[1mSegID specification only valid for PSF-DCD specification (not PDB). Abort.\033[0m\n");
				myexit(1);
				}
				
                        if ( sscanf( argv[i+1], "%s", &junk[0] ) != 1 )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-segid\".\033[0m\n");
					myexit( 1 );
                                                        }

			i++;
                        if ( strlen( argv[i] ) > 5 )
                        	{
                        		printf("\033[31m\033[1mSegID specification error : string (%s) too long.\033[0m\n", argv[i] );
                        		myexit(1);
                        				}
                        if ( strlen( argv[i] ) < 5 )
				strncpy( &inter[1], argv[i], strlen(argv[i]) );
                        else
				strncpy( &inter[0], argv[i], strlen(argv[i]) );

			if ( HAVE_SEGID == YES )
				{
					for ( m=0 ; m < strlen( SEGID ) ; m += 5 )
						if ( strncasecmp( &inter[0], &SEGID[m], 5) == 0 )
							{
							printf("\033[31m\033[1mSame SEGID given twice ? (%s). Abort.\033[0m\n", inter);
							myexit(1);
							}
				}
				
			strcat( &SEGID[0], &inter[0] );

                        HAVE_SEGID = YES;
                        
                        
								}
	else if ( strncasecmp( argv[i], "-FIT", 4) == 0 )
		{
			if ( HAVE_PSF == NO || HAVE_DCD == NO )
				{
				printf("\033[31m\033[1mFIT keyword only meaningful for a DCD-PSF run. Abort.\033[0m\n");
				myexit(1);
				}

                        DO_FIT = YES;
                        
								}
	else if ( strncasecmp( argv[i], "-CRO", 4) == 0 )
		{
			if ( HAVE_PSF == NO || HAVE_DCD == NO )
				{
				printf("\033[31m\033[1mCROSS keyword only meaningful for a DCD-PSF run. Abort.\033[0m\n");
				myexit(1);
				}

                        CROSSDCD = YES;
                        DO_FIT = NO;
#ifdef GRA
			GRAPHICS = NO;
#endif                        
								}
	else if ( strncasecmp( argv[i], "-QF", 3) == 0 )
		{
                        if ( sscanf( argv[i+1], "%f", &Q_CUTOFF ) != 1 )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-Qfraction\".\033[0m\n");
					myexit( 1 );
                                                        }

                        if ( sscanf( argv[i+2], "%d", &Q_SEPARATION ) != 1 )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-Qfraction\".\033[0m\n");
					myexit( 1 );
                                                        }

			QFRACTION = YES;
                        i += 2;
                                                        	}
	else if ( strncasecmp( argv[i], "-PDB", 4) == 0 )
		{
			if ( HAVE_PSF == NO || HAVE_DCD == NO )
				{
				printf("\033[31m\033[1mPDB keyword only meaningful for a DCD-PSF run. Abort.\033[0m\n");
				myexit(1);
				}

                        WRITE_PDB = YES;
                        
								}
	else if ( strncasecmp( argv[i], "-SUP", 4) == 0 )
		{
			if ( HAVE_PSF == NO || HAVE_DCD == NO )
				{
				printf("\033[31m\033[1m'-super' keyword only meaningful for a DCD-PSF run. Abort.\033[0m\n");
				myexit(1);
				}

                        WRITE_SUPER = YES;
                        
								}
#ifndef WINDOWS
	else if ( strncasecmp( argv[i], "-STR", 4) == 0 )
		{
			if ( HAVE_PSF == NO || HAVE_DCD == NO )
				{
				printf("\033[31m\033[1mSTRIDE keyword only meaningful for a DCD-PSF run. Abort.\033[0m\n");
				myexit(1);
				}

                        STRIDE = YES;
                        
								}
#endif
	else if ( strncasecmp( argv[i], "-NOF", 4) == 0 )
		{
			if ( HAVE_PSF == NO || HAVE_DCD == NO )
				{
				printf("\033[31m\033[1mNOFIT keyword only meaningful for a DCD-PSF run. Abort.\033[0m\n");
				myexit(1);
				}

                        DO_FIT = YES;
			NOFIT = YES;
                        
								}
	else if ( strncasecmp( argv[i], "-I", 2) == 0 )
		{
			if ( HAVE_PSF == NO || HAVE_DCD == NO )
				{
				printf("\033[31m\033[1mINDEX keyword only meaningful for a DCD-PSF run. Abort.\033[0m\n");
				myexit(1);
				}

                        HAVE_INDEX = YES;

                        
								}
	else if ( strncasecmp( argv[i], "-PDD", 4) == 0 )
		{
			if ( HAVE_PSF == NO || HAVE_DCD == NO )
				{
				printf("\033[31m\033[1mPDDF keyword only meaningful for a DCD-PSF run. Abort.\033[0m\n");
				myexit(1);
				}

                        PDDF = YES;

                        
								}
	else if ( strncasecmp( argv[i], "-3D", 3) == 0 )
		{
			if ( HAVE_PSF == NO || HAVE_DCD == NO )
				{
				printf("\033[31m\033[1m3D keyword only meaningful for a DCD-PSF run. Abort.\033[0m\n");
				myexit(1);
				}

                        MAKE_3D = YES;
                        
								}
	else if ( strncasecmp( argv[i], "-SI", 3) == 0 )
		{

                        if ( sscanf( argv[i+1], "%f", &LAMBDA ) != 1 )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-sigmoidal\".\033[0m\n");
					myexit( 1 );
                                                        }
                        i++;

                        SIGMOIDAL = YES;
                        
								}

	else if ( strncasecmp( argv[i], "-DI", 3) == 0 )
		{								
			if ( sscanf( argv[i+1], "%d", &DISTFIRST ) != 1 )	/* Is it a file with pairs ? */
				{
					FILE	*test;
					
					strcpy( DIST_NAME, argv[i+1] );
					test = fopen( DIST_NAME, "r" );
					if ( test == NULL )
		                                {
        		                                printf("\033[31m\033[1mProblem with the argument to \"-distance\".\033[0m\n");
							myexit( 1 );
                                        	 	               }
                                        else
                                        {
                                        	fclose( test );
                                        	i += 1;
                                        	HAVE_DISTANCE_FILE = YES;
                                        }	 	               
				}
			else
			{
                        if ( sscanf( argv[i+2], "%d", &DISTSECOND ) != 1  )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-distance\".\033[0m\n");
					myexit( 1 );
                                                        }
			DISTFIRST--;
			DISTSECOND--;
                        i += 2;
                        }
                                                        	}
	else if ( strncasecmp( argv[i], "-TO", 3) == 0 )
		{
			if ( sscanf( argv[i+1], "%d", &TORSFIRST ) != 1 )	/* Is it a file with tetraplets ? */
				{
					FILE	*test;
					
					strcpy( TORS_NAME, argv[i+1] );
					test = fopen( TORS_NAME, "r" );
					if ( test == NULL )
		                                {
        		                                printf("\033[31m\033[1mProblem with the argument to \"-torsion\".\033[0m\n");
							myexit( 1 );
                                        	 	               }
                                        else
                                        {
                                        	fclose( test );
                                        	i += 1;
                                        	HAVE_TORSION_FILE = YES;
                                        }	 	               
				}
			else
			{
                        if ( sscanf( argv[i+2], "%d", &TORSSECOND ) != 1  )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-torsion\".\033[0m\n");
					myexit( 1 );
                                                        }
                        if ( sscanf( argv[i+3], "%d", &TORSTHIRD ) != 1  )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-torsion\".\033[0m\n");
					myexit( 1 );
                                                        }
                        if ( sscanf( argv[i+4], "%d", &TORSFOURTH ) != 1  )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-torsion\".\033[0m\n");
					myexit( 1 );
                                                        }
			TORSFIRST--;
			TORSSECOND--;
			TORSTHIRD--;
			TORSFOURTH--;
                        i += 4;
                        }
                                                        	}

    else if ( strncasecmp( argv[i], "-BE", 3) == 0 )
        {
			if ( sscanf( argv[i+1], "%d", &BENDFIRST ) != 1 )	/* Is it a file with triplets ? */
				{
					FILE	*test;
					
					strcpy( BEND_NAME, argv[i+1] );
					test = fopen( BEND_NAME, "r" );
					if ( test == NULL )
		                                {
        		                                printf("\033[31m\033[1mProblem with the argument to \"-bend\".\033[0m\n");
							myexit( 1 );
                                        	 	               }
                                        else
                                        {
                                        	fclose( test );
                                        	i += 1;
                                        	HAVE_BEND_FILE = YES;
                                        }	 	               
				}
			else
			{
                        if ( sscanf( argv[i+1], "%d", &BENDFIRST ) != 1  )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-bendangle\".\033[0m\n");
                                        myexit( 1 );
                                                        }
                        if ( sscanf( argv[i+2], "%d", &BENDSECOND ) != 1  )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-bendangle\".\033[0m\n");
                                        myexit( 1 );
                                                        }
                        if ( sscanf( argv[i+3], "%d", &BENDTHIRD ) != 1  )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-bendangle\".\033[0m\n");
					myexit( 1 );
                                                        }
			BENDFIRST--;
			BENDSECOND--;
			BENDTHIRD--;
                        i += 3;
                        }
                                                            }

#ifdef GRA
	else if ( strncasecmp( argv[i], "-G", 2) == 0 )
		{

                        if ( sscanf( argv[i+1], "%f", &GRABOX ) != 1 )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-graphics\".\033[0m\n");
					myexit( 1 );
                                                        }
                        i++;
			GRABOX = fabs(GRABOX);
			CROSS = GRABOX / 60.0;
                        GRAPHICS = YES;
                        
								}
	else if ( strncasecmp( argv[i], "-LO", 3) == 0 )
		{

			LOOP = YES;                        
								}
	else if ( strncasecmp( argv[i], "-CP", 3) == 0 )
		{

			CPK = YES;                        
								}
	else if ( strncasecmp( argv[i], "-TRA", 4) == 0 )
		{
			TRICK = YES;
								}
	else if ( strncasecmp( argv[i], "-SP", 3) == 0 )
		{
			GRADIENT = YES;
								}
#endif
	else if ( strncasecmp( argv[i], "-REF", 4) == 0 )
		{
			if ( HAVE_PSF == NO || HAVE_DCD == NO )
				{
				printf("\033[31m\033[1mReference frame specification only meaningful for a DCD-PSF run. Abort.\033[0m\n");
				myexit(1);
				}

                        if ( sscanf( argv[i+1], "%d", &REFERENCE ) != 1 )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-reference\".\033[0m\n");
					myexit( 1 );
                                                        }
			if ( sscanf( argv[i+2], "%d", &REF_STEP ) == 1  )
				{
					if ( VERBOSE )
					printf("\033[32mIncremental rmsds requested. Step is %d.\033[0m\n", REF_STEP );
					i++;
				}
                        i++;
                        if ( REFERENCE <= 0 )
                        	{
                        		printf("\033[31m\033[1mReference frame number must be a positive integer.\033[0m\n");
                        		myexit(1);
                        				}

                        DO_FIT = YES;
                        
								}
	else if ( strncasecmp( argv[i], "-STE", 4) == 0 )
		{
			if ( HAVE_PDB != NO )
				printf("\033[31m\033[1mFrame specification for a .pdb file ? Ignored.\033[0m\n");
				
                        if ( sscanf( argv[i+1], "%d", &STEP ) != 1 )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-step\".\033[0m\n");
					myexit( 1 );
                                                        }
                        i++;
                        if ( STEP <= 0 )
                        	{
                        		printf("\033[31m\033[1mFrame step numbers must be positive integers.\033[0m\n");
                        		myexit(1);
                        				}
                        
								}
	else if ( strncasecmp( argv[i], "-MI", 3) == 0 )
		{
			HAVE_MIN = YES;
                        if ( sscanf( argv[i+1], "%f", &gmin ) != 1 )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-min\".\033[0m\n");
					myexit( 1 );
                                                        }
                        i++;
                                                        	}
	else if ( strncasecmp( argv[i], "-MAX", 4) == 0 )
		{
			HAVE_MAX = YES;
                        if ( sscanf( argv[i+1], "%f", &gmax ) != 1 )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-max\".\033[0m\n");
					myexit( 1 );
                                                        }
                        i++;
                                                        	}
	else if ( strncasecmp( argv[i], "-DG", 3) == 0 )
		{
                        if ( sscanf( argv[i+1], "%f", &DGLEN ) != 1 )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-DGwidth\".\033[0m\n");
					myexit( 1 );
                                                        }
                        i++;
                                                        	}
	else if ( strncasecmp( argv[i], "-COL", 4) == 0 )
		{
			float	test;

			COLOUR = YES;					
										/* If no numbers follow, use defaults */
                        if ( argc > (i+2) && strncasecmp( argv[i+1], "-", 1) != 0 && sscanf( argv[i+1], "%f", &test ) == 1 )
                        {	
                        					                /* else read 15 floats */
			if ( argc < (i+16) )
                                {
                                        printf("\033[31m\033[1mFlag \"-colour\" expects 15 floats.\033[0m\n");
					myexit( 1 );
                                                        }

                        if ( sscanf( argv[i+1], "%f", &RED_1 ) != 1  )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-colour\".\033[0m\n");
					myexit( 1 );
                                                        }
                        if ( sscanf( argv[i+2], "%f", &GREEN_1 ) != 1  )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-colour\".\033[0m\n");
					myexit( 1 );
                                                        }
                        if ( sscanf( argv[i+3], "%f", &BLUE_1 ) != 1  )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-colour\".\033[0m\n");
					myexit( 1 );
                                                        }
                        if ( sscanf( argv[i+4], "%f", &RED_2 ) != 1  )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-colour\".\033[0m\n");
					myexit( 1 );
                                                        }
                        if ( sscanf( argv[i+5], "%f", &GREEN_2 ) != 1  )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-colour\".\033[0m\n");
					myexit( 1 );
                                                        }
                        if ( sscanf( argv[i+6], "%f", &BLUE_2 ) != 1  )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-colour\".\033[0m\n");
					myexit( 1 );
                                                        }
                        if ( sscanf( argv[i+7], "%f", &RED_3 ) != 1  )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-colour\".\033[0m\n");
					myexit( 1 );
                                                        }
                        if ( sscanf( argv[i+8], "%f", &GREEN_3 ) != 1  )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-colour\".\033[0m\n");
					myexit( 1 );
                                                        }
                        if ( sscanf( argv[i+9], "%f", &BLUE_3 ) != 1  )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-colour\".\033[0m\n");
					myexit( 1 );
                                                        }
                        if ( sscanf( argv[i+10], "%f", &RED_4 ) != 1  )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-colour\".\033[0m\n");
					myexit( 1 );
                                                        }
                        if ( sscanf( argv[i+11], "%f", &GREEN_4 ) != 1  )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-colour\".\033[0m\n");
					myexit( 1 );
                                                        }
                        if ( sscanf( argv[i+12], "%f", &BLUE_4 ) != 1  )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-colour\".\033[0m\n");
					myexit( 1 );
                                                        }
                        if ( sscanf( argv[i+13], "%f", &RED_5 ) != 1  )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-colour\".\033[0m\n");
					myexit( 1 );
                                                        }
                        if ( sscanf( argv[i+14], "%f", &GREEN_5 ) != 1  )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-colour\".\033[0m\n");
					myexit( 1 );
                                                        }
                        if ( sscanf( argv[i+15], "%f", &BLUE_5 ) != 1  )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-colour\".\033[0m\n");
					myexit( 1 );
                                                        }

			if ( 	RED_1 < 0.0 || RED_1 > 1.0 || RED_2 < 0.0 || RED_2 > 1.0 ||
				RED_3 < 0.0 || RED_3 > 1.0 || RED_4 < 0.0 || RED_4 > 1.0 || RED_5 < 0.0 || RED_5 > 1.0 || 
				GREEN_1 < 0.0 || GREEN_1 > 1.0 || GREEN_2 < 0.0 || GREEN_2 > 1.0 ||
                                GREEN_3 < 0.0 || GREEN_3 > 1.0 || GREEN_4 < 0.0 || GREEN_4 > 1.0 || GREEN_5 < 0.0 || GREEN_5 > 1.0 || 
				BLUE_1 < 0.0 || BLUE_1 > 1.0 || BLUE_2 < 0.0 || BLUE_2 > 1.0 ||
                                BLUE_3 < 0.0 || BLUE_3 > 1.0 || BLUE_4 < 0.0 || BLUE_4 > 1.0 || BLUE_5 < 0.0 || BLUE_5 > 1.0 )
                                {
                                        printf("\033[31m\033[1mArguments to \"-colour\" must be between 0.0 and 1.0.\033[0m\n");
					myexit( 1 );
                                                        }
			

			
			i += 15;
								}	
                                                        		}
	else if ( strncasecmp( argv[i], "-MR", 3) == 0 )
		{
			if ( HAVE_PDB != NO )
				printf("\033[31m\033[1mFrame rmsd specification for a .pdb file ? Ignored.\033[0m\n");
                        if ( sscanf( argv[i+1], "%f", &MAX_RMSD ) != 1 || MAX_RMSD <= 0.0 )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-mrms\".\033[0m\n");
					myexit( 1 );
                                                        }
                        i++;
                                                        	}
	else if ( strncasecmp( argv[i], "-MAP", 4) == 0 )
		{
                        if ( sscanf( argv[i+1], "%f", &Xmin ) != 1  )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-map\".\033[0m\n");
					myexit( 1 );
                                                        }
                        if ( sscanf( argv[i+2], "%f", &Xmax ) != 1  )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-map\".\033[0m\n");
					myexit( 1 );
                                                        }
                        if ( sscanf( argv[i+3], "%f", &Ymin ) != 1  )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-map\".\033[0m\n");
					myexit( 1 );
                                                        }
                        if ( sscanf( argv[i+4], "%f", &Ymax ) != 1  )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-map\".\033[0m\n");
					myexit( 1 );
                                                        }
                        if ( sscanf( argv[i+5], "%f", &Zmin ) != 1  )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-map\".\033[0m\n");
					myexit( 1 );
                                                        }
                        if ( sscanf( argv[i+6], "%f", &Zmax ) != 1  )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-map\".\033[0m\n");
					myexit( 1 );
                                                        }
                        if ( sscanf( argv[i+7], "%f", &Grid ) != 1  )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-map\".\033[0m\n");
					myexit( 1 );
                                                        }

			if ( Xmin > Xmax )
				{
					temp = Xmin;
					Xmin = Xmax;
					Xmax = temp;
							}
			if ( Ymin > Ymax )
				{
					temp = Ymin;
					Ymin = Ymax;
					Ymax = temp;
							}
			if ( Zmin > Zmax )
				{
					temp = Zmin;
					Zmin = Zmax;
					Zmax = temp;
							}
			if ( Xmin == Xmax || Ymin == Ymax || Zmin == Zmax )
                                {
                                        printf("\033[31m\033[1mOnly 3D density maps are supported.\033[0m\n");
					myexit( 1 );
                                                        }

			if ( Grid <= 0.0 )
                                {
                                        printf("\033[31m\033[1mProblem with the grid argument to \"-map\".\033[0m\n");
					myexit( 1 );
                                                        }
				
			CALC_MAP = YES;
                        i += 7;
                                                        	}
	else if ( strncasecmp( argv[i], "-CRY", 4) == 0 )
		{
                        if ( sscanf( argv[i+1], "%lf", &f2o_11 ) != 1  )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-crystal\".\033[0m\n");
					myexit( 1 );
                                                        }
                        if ( sscanf( argv[i+2], "%lf", &f2o_12 ) != 1  )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-crystal\".\033[0m\n");
					myexit( 1 );
                                                        }
                        if ( sscanf( argv[i+3], "%lf", &f2o_13 ) != 1  )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-crystal\".\033[0m\n");
					myexit( 1 );
                                                        }
                        if ( sscanf( argv[i+4], "%lf", &f2o_14 ) != 1  )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-crystal\".\033[0m\n");
					myexit( 1 );
                                                        }
                        if ( sscanf( argv[i+5], "%lf", &f2o_21 ) != 1  )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-crystal\".\033[0m\n");
					myexit( 1 );
                                                        }
                        if ( sscanf( argv[i+6], "%lf", &f2o_22 ) != 1  )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-crystal\".\033[0m\n");
					myexit( 1 );
                                                        }
                        if ( sscanf( argv[i+7], "%lf", &f2o_23 ) != 1  )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-crystal\".\033[0m\n");
					myexit( 1 );
                                                        }
                        if ( sscanf( argv[i+8], "%lf", &f2o_24 ) != 1  )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-crystal\".\033[0m\n");
					myexit( 1 );
                                                        }
                        if ( sscanf( argv[i+9], "%lf", &f2o_31 ) != 1  )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-crystal\".\033[0m\n");
					myexit( 1 );
                                                        }
                        if ( sscanf( argv[i+10], "%lf", &f2o_32 ) != 1  )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-crystal\".\033[0m\n");
					myexit( 1 );
                                                        }
                        if ( sscanf( argv[i+11], "%lf", &f2o_33 ) != 1  )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-crystal\".\033[0m\n");
					myexit( 1 );
                                                        }
                        if ( sscanf( argv[i+12], "%lf", &f2o_34 ) != 1  )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-crystal\".\033[0m\n");
					myexit( 1 );
                                                        }

                        if ( sscanf( argv[i+13], "%d", &cryst_x ) != 1  )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-crystal\".\033[0m\n");
					myexit( 1 );
                                                        }
                        if ( sscanf( argv[i+14], "%d", &cryst_y ) != 1  )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-crystal\".\033[0m\n");
					myexit( 1 );
                                                        }
                        if ( sscanf( argv[i+15], "%d", &cryst_z ) != 1  )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-crystal\".\033[0m\n");
					myexit( 1 );
                                                        }

/*			printf("%20.17f %20.17f %20.17f %20.17f %20.17f %20.17f %20.17f %20.17f %20.17f %20.17f %20.17f %20.17f\n", 
					  f2o_11, f2o_12, f2o_13, f2o_14,
					  f2o_21, f2o_22, f2o_23, f2o_24,
					  f2o_31, f2o_32, f2o_33, f2o_34 );
*/			
			 
			CALC_MAP = YES;
			CRYSTALLOGRAPHIC_FRAME = YES;
                        i += 15;
                                                        	}

	else if ( strncasecmp( argv[i], "-FM", 3) == 0 )
		{
                        if ( sscanf( argv[i+1], "%f", &Xmin ) != 1  )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-fmap\".\033[0m\n");
					myexit( 1 );
                                                        }
                        if ( sscanf( argv[i+2], "%f", &Xmax ) != 1  )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-fmap\".\033[0m\n");
					myexit( 1 );
                                                        }
                        if ( sscanf( argv[i+3], "%f", &Ymin ) != 1  )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-fmap\".\033[0m\n");
					myexit( 1 );
                                                        }
                        if ( sscanf( argv[i+4], "%f", &Ymax ) != 1  )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-fmap\".\033[0m\n");
					myexit( 1 );
                                                        }
                        if ( sscanf( argv[i+5], "%f", &Zmin ) != 1  )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-fmap\".\033[0m\n");
					myexit( 1 );
                                                        }
                        if ( sscanf( argv[i+6], "%f", &Zmax ) != 1  )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-fmap\".\033[0m\n");
					myexit( 1 );
                                                        }
                        if ( sscanf( argv[i+7], "%f", &Grid ) != 1  )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-fmap\".\033[0m\n");
					myexit( 1 );
                                                        }

			if ( Xmin > Xmax )
				{
					temp = Xmin;
					Xmin = Xmax;
					Xmax = temp;
							}
			if ( Ymin > Ymax )
				{
					temp = Ymin;
					Ymin = Ymax;
					Ymax = temp;
							}
			if ( Zmin > Zmax )
				{
					temp = Zmin;
					Zmin = Zmax;
					Zmax = temp;
							}
			if ( Xmin == Xmax || Ymin == Ymax || Zmin == Zmax )
                                {
                                        printf("\033[31m\033[1mOnly 3D density maps are supported.\033[0m\n");
					myexit( 1 );
                                                        }

			if ( Grid <= 0.0 )
                                {
                                        printf("\033[31m\033[1mProblem with the grid argument to \"-fmap\".\033[0m\n");
					myexit( 1 );
                                                        }
				
			FAST_MAP = YES;
                        i += 7;
                                                        	}
#if defined (LAPACK) || defined (NR)
	else if ( strncasecmp( argv[i], "-PR", 3) == 0 )
		{
			
                        if ( sscanf( argv[i+1], "%d", &EIGENLAST ) != 1  )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-proj\".\033[0m\n");
					myexit( 1 );
                                                        }
                        if ( sscanf( argv[i+2], "%d", &DG_PLOTS ) != 1  )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-proj\".\033[0m\n");
					myexit( 1 );
                                                        }
                        if ( sscanf( argv[i+3], "%f", &DGTEMP ) != 1  )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-proj\".\033[0m\n");
					myexit( 1 );
                                                        }
			if ( strncasecmp( argv[i+4], "-", 1) != 0 && sscanf( argv[i+4], "%f", &CLU_RMS ) == 1  )
				{
					if ( VERBOSE )
					printf("\033[32mCutoff for cluster selection set to mean%+f sigma.\033[0m\n", CLU_RMS );
					i++;
				}

			EIGENFIRST = 1;
			EIGENSTEP  = 1;

                        if ( EIGENLAST < 2 )
                                {
                                        printf("\033[31m\033[1mLess than two eigenvectors requested for \"-proj\" ? Abort.\033[0m\n");
					myexit( 1 );
                                                        }

			if ( DG_PLOTS < 2 || DG_PLOTS > EIGENLAST )
	         		{						/* Fascism */
					DG_PLOTS = 2;
                                                        }
			if ( DGTEMP < 10.0 )
                                {
                                        printf("\033[31m\033[1mIt is cold out there ... Check the man page for \"-proj\".\033[0m\n");
					myexit( 1 );
                                                        }

                        i += 3;
                                                        	}
	else if ( strncasecmp( argv[i], "-DP", 3) == 0 )
		{
			
                        if ( sscanf( argv[i+1], "%d", &EIGENLAST ) != 1  )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-dPCA\".\033[0m\n");
					myexit( 1 );
                                                        }
                        if ( sscanf( argv[i+2], "%d", &DG_PLOTS ) != 1  )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-dPCA\".\033[0m\n");
					myexit( 1 );
                                                        }
                        if ( sscanf( argv[i+3], "%f", &DGTEMP ) != 1  )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-dPCA\".\033[0m\n");
					myexit( 1 );
                                                        }
			if ( strncasecmp( argv[i+4], "-", 1) != 0 && sscanf( argv[i+4], "%f", &CLU_RMS ) == 1  )
				{
					if ( VERBOSE )
					printf("\033[32mCutoff for cluster selection set to mean%+f sigma.\033[0m\n", CLU_RMS );
					i++;
				}

			EIGENFIRST = 1;
			EIGENSTEP  = 1;

                        if ( EIGENLAST < 2 )
                                {
                                        printf("\033[31m\033[1mLess than two eigenvectors requested for \"-dPCA\" ? Abort.\033[0m\n");
					myexit( 1 );
                                                        }

			if ( DG_PLOTS < 2 || DG_PLOTS > EIGENLAST )
	         		{						/* Fascism */
					DG_PLOTS = 2;
                                                        }
			if ( DGTEMP < 10.0 )
                                {
                                        printf("\033[31m\033[1mIt is cold out there ... Check the man page for \"-dPCA\".\033[0m\n");
					myexit( 1 );
                                                        }

			DPCA = YES;
                        i += 3;
                                                        	}
	else if ( strncasecmp( argv[i], "-CHI", 4) == 0 )
		{
			CHI1 = YES;
		}
	else if ( strncasecmp( argv[i], "-PL", 3) == 0 )
		{
                        if ( sscanf( argv[i+1], "%d", &EIGENPLAY ) != 1 || EIGENPLAY < 1 )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-play\".\033[0m\n");
					myexit( 1 );
                                                        }
                        if ( sscanf( argv[i+2], "%f", &EIGENPLAY_FIRST ) != 1  )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-play\".\033[0m\n");
					myexit( 1 );
                                                        }
                        if ( sscanf( argv[i+3], "%f", &EIGENPLAY_LAST ) != 1  )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-play\".\033[0m\n");
					myexit( 1 );
                                                        }
                        i += 3;
                                                        	}
	else if ( strncasecmp( argv[i], "-O", 2) == 0 )
		{
                        if ( sscanf( argv[i+1], "%d", &EIGENFIRST_W ) != 1  )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-out\".\033[0m\n");
					myexit( 1 );
                                                        }
                        if ( sscanf( argv[i+2], "%d", &EIGENLAST_W ) != 1  )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-out\".\033[0m\n");
					myexit( 1 );
                                                        }
                        if ( sscanf( argv[i+3], "%d", &EIGENSTEP_W ) != 1  )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-out\".\033[0m\n");
					myexit( 1 );
                                                        }
                        if ( EIGENFIRST_W < 1 || EIGENFIRST_W > EIGENLAST_W || EIGENSTEP_W < 1 )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-out\".\033[0m\n");
					myexit( 1 );
                                                        }
                        i += 3;
                                                        	}
	else if ( strncasecmp( argv[i], "-AR", 3) == 0 )
		{
                        if ( sscanf( argv[i+1], "%d", &ART_EIGEN ) != 1  )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-artificial\".\033[0m\n");
					myexit( 1 );
                                                        }
                        if ( sscanf( argv[i+2], "%d", &ART_FRAMES ) != 1  )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-artificial\".\033[0m\n");
					myexit( 1 );
                                                        }
                        if ( ART_EIGEN < 1 || ART_FRAMES < 1 )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-artificial\".\033[0m\n");
					myexit( 1 );
                                                        }
                        i += 2;
                                                        	}
	else if ( strncasecmp( argv[i], "-TE", 3) == 0 )
		{
			ENTROPY = YES;
                        if ( sscanf( argv[i+1], "%f", &Temp ) != 1 )
                                {
                                        printf("\033[31m\033[1mProblem with the argument to \"-temp\".\033[0m\n");
					myexit( 1 );
                                                        }
                        i++;
                                                        	}
	else if ( strncasecmp( argv[i], "-SH", 3) == 0 )
		{
			SHANNON = YES;
		}
#endif
	else if ( strncasecmp( argv[i], "-RM", 3) == 0 )
		{
			if ( HAVE_PDB != NO )
				printf("\033[31m\033[1mFrame rmsd specification for a .pdb file ? Ignored.\033[0m\n");
			FIND_RMS = YES;
		}
	else if ( strncasecmp( argv[i], "-RG", 3) == 0 )
		{
			GYRATION = YES;
		}
	else if ( strncasecmp( argv[i], "-SUR", 4) == 0 )
		{
			ASA = YES;
		}
	else if ( strncasecmp( argv[i], "-COV", 4) == 0 )
		{
			if ( HAVE_PDB != NO )
				printf("\033[31m\033[1mCovariance request for .pdb file ? Ignored.\033[0m\n");
			FIND_COV = YES;
		}
	else if ( strncasecmp( argv[i], "-DO", 3) == 0 )
		USE_DOT = YES;
	else if ( strncasecmp( argv[i], "-NOR", 4) == 0 )
		NORMALISE = YES;
	else if ( strncasecmp( argv[i], "-W", 2) == 0 )
		WRITE_DATA = YES;
	else if ( strncasecmp( argv[i], "-REV", 4) == 0 )
		REVERSE = YES;
	else if ( strncasecmp( argv[i], "-REP", 4) == 0 )
		REPOSITION = YES;
	else if ( strncasecmp( argv[i], "-NOC", 4) == 0 )
		WRITE_CAS = NO;
#if defined (LAPACK) || defined (NR)
	else if ( strncasecmp( argv[i], "-E", 2) == 0 )
		EIGEN = YES;
	else if ( strncasecmp( argv[i], "-U", 2) == 0 )
		USE_LAST = YES;
#endif
	else if ( strncasecmp( argv[i], "-MAS", 4) == 0 )
		MASSES = YES;
	else if ( strcmp( argv[i], "-") == 0 )
		FILTER = YES;
	else if ( strncasecmp( argv[i], "-V", 2) == 0 )
		VERBOSE = YES;
	else if ( strncasecmp( &argv[i][ strlen( argv[i]) - 4], ".PDB", 4) == 0 )
		;
	else if ( strncasecmp( &argv[i][ strlen( argv[i]) - 4], ".DCD", 4) == 0 )
		;
	else if ( strncasecmp( &argv[i][ strlen( argv[i]) - 4], ".PSF", 4) == 0 )
		;
	else 
		{
			printf("\033[31m\033[1mUnidentified keyword or argument : %s. Abort.\n", argv[i] );
			myexit( 1 );
					}
	}
	




/*****************************************************************************************************************************/
/**	Sanity checks													    **/
/*****************************************************************************************************************************/

	if ( FILTER == YES )
		{
			VERBOSE = NO;
			filter();
					}
					
	
	
	if ( LAST > 0 && FIRST > 0 && LAST < FIRST )
		{
			tempr = LAST;
			LAST = FIRST;
			FIRST = tempr;
					}

#ifdef WINDOWS
	if ( STRIDE == YES )
		{
			printf("\033[31m\033[1mSorry. \"-stride\" is only functional on unix machines.\033[0m\n");
			myexit(1);	
		}
#endif

	if ( STRIDE == YES && WRITE_PDB != YES )
		{
			printf("\033[31m\033[1mThe \"-stride\" flag requires \"-pdb\" as well.\033[0m\n");
			myexit(1);	
					}


	if ( ( HAVE_DCD != NO && HAVE_PSF == NO ) || ( HAVE_DCD == NO && HAVE_PSF != NO ))
		{
			printf("\033[31m\033[1mFor a PSF-DCD run both a PSF and a DCD file are needed.\033[0m\n");
			myexit(1);	
					}

	if ( DPCA == YES )
		{
			if (  HAVE_DCD == NO || HAVE_PSF == NO )
			{
			printf("\033[31m\033[1mThe \"-dPCA\" flag only relevant for PSF-DCD.\033[0m\n");
			myexit(1);	
			}

			if ( MASSES == YES )
			{
			printf("\033[33mDoes the \"-masses\" + \"-dPCA\" flags make sense ? Continue.\033[0m\n");
			}

			if ( HAVE_SEGID == NO )
			{
			printf("\033[31m\033[1mThe \"-dPCA\" flag requires at least one segid selection.\033[0m\n");
			myexit(1);	
			}
									/* Force atom selection needed for dihedrals */
			if ( CHI1 == NO )
			{
				ALL_ATID = NO;
				HEAVY = NO;
				strncpy( ATOMID, " N    CA   C   ", 16 );
			}
			else
			{
				ALL_ATID = NO;
				HEAVY = NO;
				strncpy( ATOMID, " N    CA   C    CG   CG1  OG   OG1  SG   CB  ", 46 );
			}
		}

	
	if ( CALC_MAP == YES && ( HAVE_DCD == NO || HAVE_PSF == NO ))
		{
			printf("\033[31m\033[1mThe \"-map\" flag only relevant for PSF-DCD.\033[0m\n");
			myexit(1);	
					}

	if ( GYRATION == YES && ( HAVE_DCD == NO || HAVE_PSF == NO ))
		{
			printf("\033[31m\033[1mThe \"-rg\" flag only relevant for PSF-DCD.\033[0m\n");
			myexit(1);	
					}
	if ( ASA == YES )
		{
			if ( HAVE_DCD == NO || HAVE_PSF == NO )
			{
			printf("\033[31m\033[1mThe \"-surf\" flag only relevant for PSF-DCD.\033[0m\n");
			myexit(1);	
			}
			if ( HAVE_SEGID == NO )
			{
			printf("\033[31m\033[1mThe \"-surf\" flag requires at least one segid selection.\033[0m\n");
			myexit(1);	
			}
									/* Ignore hydrogens for ASA */
			HEAVY = YES;
			ALL_ATID = NO;
		}


	if ( MAX_RMSD >= 0.0 && FIND_RMS == NO )
		printf("\033[31m\033[1m\"-mrms\" specified but not \"-rms\" ? Ignored.\033[0m\n");


	if ( FIND_RMS == YES && FIND_COV == YES )
		{
			printf("\033[31m\033[1mCan not calculate rms and covariance matrices in one pass.\033[0m\n");
			myexit(1);	
					}

	if ( (USE_DOT == YES || NORMALISE == YES) && FIND_COV == NO )
		printf("\033[31m\033[1mThe \"-norm\" and \"-dot\" flags are not relevant. Ignored.\033[0m\n");

	if ( DO_FIT != YES && HAVE_INDEX == YES )
		{
		printf("\033[31m\033[1mHave \"-index\" flag in the absence of \"-fit\" ? Abort.\033[0m\n");
		myexit(1);
		}

	if ( strlen(ATOMID) < 5 )
		{
		strncpy( ATOMID, " CA  ", 6 );
#ifdef GRA
		if ( HAVE_SEGID == NO && !CPK )
			GRADIENT = YES;
#endif
		}
	else
		{
#ifdef GRA
			if ( HAVE_SEGID == NO && !GRADIENT)
				CPK = YES;
#endif
						}

	if ( ALL_ATID == YES || HEAVY==YES)
		{
		strncpy( ATOMID, "     ", 6 );
		}
	

	if ( MASSES == YES && FIND_COV == NO && CALC_MAP == NO )
		{
		printf("\033[31m\033[1mThe \"-mass\" flag without \"-cov\" option ? Abort.\033[0m\n");
		myexit(1);
		}

	if ( FAST_MAP && CALC_MAP )
		{
		printf("\033[31m\033[1mUse either \"-map\" or \"-fmap\". Abort.\033[0m\n");
		myexit(1);
		}
	if ( FAST_MAP && !DO_FIT )
		{
		printf("\033[31m\033[1m\"-fmap\" requires \"-fit\". Abort.\033[0m\n");
		myexit(1);
		}
	if ( CALC_MAP && DO_FIT )
		{
		printf("\033[31m\033[1mUse \"-fmap\" instead of \"-map\" if you want to \"-fit\". Abort.\033[0m\n");
		myexit(1);
		}


#if defined (LAPACK) || defined (NR)
	if ( (EIGEN == YES || EIGENFIRST > 0 || EIGENFIRST_W > 0 || EIGENPLAY > 0 ) && FIND_COV == NO && DPCA == NO)
		{
		printf("\033[31m\033[1mThe \"-cov\" flag is needed for principal component analysis.\033[0m\n");
		myexit(1);
		}

	if ( EIGEN == NO && ( EIGENFIRST > 0 || EIGENFIRST_W > 0 || EIGENPLAY > 0 ) && DPCA == NO )
		{
		printf("\033[31m\033[1mThe \"-eigen\" flag is also needed for the intended calculation.\033[0m\n");
		myexit(1);
		}

	if ( EIGEN == YES && (USE_DOT == YES || NORMALISE == YES) )
		{
		printf("\033[31m\033[1mThe \"-dot\" and/or \"-norm\" flags are mutually exclusive with the \"-eigen\" flag.\033[0m\n");
		myexit(1);
		}
	if ( EIGEN == NO && USE_LAST == YES )
		{
		printf("\033[31m\033[1mThe \"-use\" flag is meaningless in the absence of the \"-eigen\" option.\033[0m\n");
		myexit(1);
		}
	if ( ENTROPY == YES && ( MASSES == NO || FIND_COV == NO || EIGEN == NO ))
		{
		printf("\033[31m\033[1mEntropy calculation requires \"-cov\", \"-eigen\" and \"-masses\".\033[0m\n");
		myexit(1);
		}
	if ( EIGENPLAY > 0 && USE_DOT == YES )
		{
			printf("\033[31m\033[1mCan not do eigenvector projection with \"-dot\" products.\033[0m\n");
			exit ( 1 );
					}
#endif				



	if ( VERBOSE )
		printf("\n\033[37m\033[1mcarma v.1.2\033[4;37m____________________________________________________________________\033[0m\n\n");

	if ( ASA == YES && VERBOSE)
		printf("\033[33mWill use all non-hydrogen atoms for surface calculation.\033[0m\n");


		

/*****************************************************************************************************************************/
/**   PDB stuff ...                                                                                                         **/
/*****************************************************************************************************************************/
		
	if ( HAVE_PDB != NO )
	{	
	nofCAs = get_pdb_coords( argv[HAVE_PDB] );
	if ( nofCAs < 2 )
		{
			if ( HAVE_SEGID == NO )
				printf("\033[31m\033[1mLess than two \"%s\" atoms found ? Abort.\033[0m\n", ATOMID);
			else
				printf("\033[31m\033[1mLess than two \"%s\" atoms found for segid \"%s\". Abort.\033[0m\n", ATOMID, SEGID);
			
			myexit(1);
					}

	if ( VERBOSE )
		printf("Read coordinates for %d %s atoms from input pdb file.\n", nofCAs, ATOMID );
	D1 = matrix( 1, nofCAs, 1, nofCAs);
	if ( VERBOSE )
		printf("Calculating distances ...\n");
	

	max = Dist();
	if (VERBOSE)
		printf("Maximum %s-%s distance is %f Å.\n", ATOMID, ATOMID, max );
	
	if ( HAVE_MIN == NO )
		gmin = 0.0;
	if ( HAVE_MAX == NO )
		gmax = max;

	if ( VERBOSE )
		printf("Will plot all distances between %f and %f\n", gmin, gmax);
	wps( D1, argv[HAVE_PDB] );


#ifndef WINDOWS
	if ( VERBOSE )
		{
		end_timer = time(NULL);
		printf("\033[32m\033[1mAll done in %1.1f minutes.\033[0m\n", (float)(end_timer-start_timer)/60.0 );
		}
#endif

	myexit(0);

	}






/*****************************************************************************************************************************/
/**   DCD and PSF part ...                                                                                                  **/
/*****************************************************************************************************************************/
/*****************************************************************************************************************************/
/**   Preliminaries & header reading ...                                                                                    **/
/*****************************************************************************************************************************/

	if ( HAVE_DCD == 0 || HAVE_PSF == 0 )
	{
		printf("\033[31m\033[1mYou need to define both a .dcd and a .psf file.\033[0m\n");
		myexit( 1 );
				}

	nofCAs = read_psf( argv[HAVE_PSF] );



	if ( REPOSITION == YES )
	{
	FILE	*indeces;
	int	reposindex;
	int	i;
	char    string[300];

	if ( VERBOSE )
		printf("\033[1m\033[36mWill change the order of atoms.\033[0m\n");


	indeces = fopen("reposition.index", "r");
	if ( indeces == NULL )
		{	
			printf("\033[31m\033[1mCan not open the 'reposition.index' file. Abort.\033[0m\n");
			myexit(1);
					}

	i = 0;
        while ( fgets( string, 299, indeces ) != NULL )
		{
			if ( sscanf( string, "%d", &reposindex) != 1 )
				{	
					printf("\033[31m\033[1mThe 'reposition.index' file is not valid. Abort.\033[0m\n");
					myexit(1);
							}
			reposindex--;

			if ( reposindex < 0 )
				{
					printf("\033[31m\033[1mNOTE : carma expects 1-based indeces in the reposition.index file.\033[0m\n");
					myexit(1);
							}

			if ( reposindex >= nofCAs )
				{	
					printf("\033[31m\033[1mToo large index in the 'reposition.index' file. Abort.\033[0m\n");
					myexit(1);
							}
			reposition[i] = posCAs[reposindex];
			i++;
		}

	fclose( indeces );

	for ( i=0 ; i < nofCAs ; i++ )
		posCAs[i] = reposition[i];

	}
	

#ifdef GRA
	if (VERBOSE && TRICK)
		printf("%d CAs found. First and last are %d and %d\n", realCAscount, TRICK_FIRST, TRICK_LAST );
#endif

	if ( nofCAs < 2 )
		{

			if ( HAVE_SEGID == NO )
				printf("\033[31m\033[1mLess than two \"%s\" atoms found ? Abort.\033[0m\n", ATOMID);
			else
				printf("\033[31m\033[1mLess than two \"%s\" atoms found for segid \"%s\". Abort.\033[0m\n", ATOMID, SEGID);
			myexit(1);
					}

	if ( VERBOSE && CHI1 == YES && DPCA == YES )
		printf("\033[33mIncluding chi1 angles in dihedral PCA.\033[0m\n");


	if ( VERBOSE )
		{ 
		if ( !HEAVY && !ALL_ATID )
			printf("\033[33m%d %s atoms are declared in the PSF file.\033[0m\n", nofCAs, ATOMID);
		else if ( HEAVY )
			printf("\033[33m%d non-hydrogen atoms are declared in the PSF file.\033[0m\n", nofCAs);
		else if ( ALL_ATID )
			printf("\033[33m%d atoms are declared in the PSF file.\033[0m\n", nofCAs);
		}
		
#ifdef WINDOWS
	dcd = open( argv[HAVE_DCD], O_RDONLY | O_BINARY | O_RANDOM );
#else
	dcd = open( argv[HAVE_DCD], O_RDONLY );
#endif

	if ( dcd == -1 )
		{
			printf("\033[31m\033[1mCan not open DCD file for read. Abort.\033[0m\n");
			myexit( 1 );
					}

	if ( read( dcd, dcd_head, (size_t)(92) ) != 92 )
		{
			printf("\033[31m\033[1mPremature EOF for DCD file ? Abort.\033[0m\n");
			myexit(1);
					}

	if ( strncasecmp( (char *)(&dcd_head[4]), "CORD", 4) != 0 )
		{
			printf("\033[31m\033[1mNot a coordinate DCD file ? Abort.\033[0m\n");
			myexit(1);
					}

	if ( 	(unsigned int)(*((unsigned int *)(&dcd_head[48]))) == 1 ||
		(unsigned int)(*((unsigned int *)(&dcd_head[48]))) == 2  )
		{
			HAVE_CELL = YES;
			CELL_OFFSET = 14;
			if ( VERBOSE )
				printf("\033[32m\033[1mIt appears that this DCD file contains unit cell information.\033[0m\n");
					}

 
	if (    (unsigned int)(*((unsigned int *)(&dcd_head[40]))) != 0 )
               {
			printf("\033[31m\033[1mDCD files with fixed atoms are not supported. Abort.\033[0m\n");
			myexit(1);
                                       }
 


	if ( (unsigned int)(*((unsigned int *)(&dcd_head[52]))) == 1 )
		{
			printf("\033[31m\033[1mIt appears that this is a CHARMM-specific DCD file. Abort.\033[0m\n");
			myexit(1);
					}
	
	
	headerframes = (unsigned int)(*((unsigned int *)(&dcd_head[8])));
	
	if ( 	(int)(*((int *)(&dcd_head[8]))) < 0 || 
		(int)(*((int *)(&dcd_head[12]))) < 0 || 
		(int)(*((int *)(&dcd_head[16]))) < 0 )
		{
			printf("\033[31m\033[1mNegative number of frames ? Wrong endian for DCD file ?\033[0m\n");
			myexit( 1 );
					}
					
	
	if ( VERBOSE )
	{				
	printf("Number of coordinate sets is %d\n", *((unsigned int *)(&dcd_head[8])));
	printf("Starting timestep         is %d\n", *((unsigned int *)(&dcd_head[12])));
	printf("Timesteps between sets    is %d\n", *((unsigned int *)(&dcd_head[16])));
	}

	
	if ( FIRST > 0 && FIRST > *((unsigned int *)(&dcd_head[8])) )
		{
			printf("\033[31m\033[1mRequested first frame does not exist. Abort.\033[0m\n");
			myexit(1);
					}
#ifdef GRA
	if ( AUTOGRA == YES )
		{
		char s[100];

		printf("\033[32m\033[1mTotal number of frames (from header) is %d\033[0m\n", *((unsigned int *)(&dcd_head[8])) );
		printf("First frame to display [1] : ");
		fgets(s, 99, stdin);
		FIRST = atoi( s );
		if ( FIRST > *((unsigned int *)(&dcd_head[8])) || FIRST < 1 )
			FIRST = 1;
		}

#endif	


	if ( read( dcd, &auint, (size_t)(4) ) != 4 )
		{
			printf("\033[31m\033[1mPremature EOF for DCD file ? Abort.\033[0m\n");
			myexit(1);
					}
	if ( read( dcd, &auint, (size_t)(4) ) != 4 )
		{
			printf("\033[31m\033[1mPremature EOF for DCD file ? Abort.\033[0m\n");
			myexit(1);
					}
	if ( auint > 0 && VERBOSE )
		printf("Titles : \n");

	for ( i=0 ; i < auint ; i++ )
		{
		if ( read( dcd, &title, (size_t)(80) ) != 80 )
		{
			printf("\033[31m\033[1mPremature EOF for DCD file ? Abort.\033[0m\n");
			myexit(1);
					}
		title[80] = 0;
		if ( VERBOSE )
			printf("%s\n", title );
		}

	if ( read( dcd, dcd_head2, (size_t)(16) ) != 16 )
		{
			printf("\033[31m\033[1mPremature EOF for DCD file ? Abort.\033[0m\n");
			myexit(1);
					}

	nofatoms = (unsigned int)(*((unsigned int *)(&dcd_head2[8])));
	
	if ( nofatoms != nofPSFatoms )
		{
			printf("\033[31m\033[1mNumber of atoms in PSF and DCD do not match. Abort.\n");
			myexit( 1 );
					}
	
	if ( VERBOSE )
		printf("Number of atoms in sets   is %d\n", nofatoms);

	
	
	
	
								/* Allocate enough memory */
	if ( HAVE_CELL == YES )
	{
	bytes_per_set = (unsigned int)(3 * ( 4 * nofatoms + 8 ) + 56);
	wbytes_per_set = (unsigned int)(3 * ( 4 * nofCAs + 8 )  + 56);
	}
	else
	{
	bytes_per_set = (unsigned int)(3 * ( 4 * nofatoms + 8 ));
	wbytes_per_set = (unsigned int)(3 * ( 4 * nofCAs + 8 ));
	}

	dcd_frame = vector( 1, bytes_per_set / 4 );
	wdcd_frame = vector( 1, wbytes_per_set / 4 );


	if ( HAVE_CELL == YES )
	{
	*((unsigned int *)(&wdcd_frame[1])) = (unsigned int)(48);
	*((unsigned int *)(&wdcd_frame[14])) = (unsigned int)(48);

	*((unsigned int *)(&wdcd_frame[14 + 1])) = (unsigned int)( nofCAs*4);
	*((unsigned int *)(&wdcd_frame[14 + 2+nofCAs])) = (unsigned int)( nofCAs*4);
	*((unsigned int *)(&wdcd_frame[14 + 3+nofCAs])) = (unsigned int)( nofCAs*4);
	*((unsigned int *)(&wdcd_frame[14 + 4+2*nofCAs])) = (unsigned int)( nofCAs*4);
	*((unsigned int *)(&wdcd_frame[14 + 5+2*nofCAs])) = (unsigned int)( nofCAs*4);
	*((unsigned int *)(&wdcd_frame[14 + 6+3*nofCAs])) = (unsigned int)( nofCAs*4);
	}
	else
	{
	*((unsigned int *)(&wdcd_frame[1])) = (unsigned int)( nofCAs*4);
	*((unsigned int *)(&wdcd_frame[2+nofCAs])) = (unsigned int)( nofCAs*4);
	*((unsigned int *)(&wdcd_frame[3+nofCAs])) = (unsigned int)( nofCAs*4);
	*((unsigned int *)(&wdcd_frame[4+2*nofCAs])) = (unsigned int)( nofCAs*4);
	*((unsigned int *)(&wdcd_frame[5+2*nofCAs])) = (unsigned int)( nofCAs*4);
	*((unsigned int *)(&wdcd_frame[6+3*nofCAs])) = (unsigned int)( nofCAs*4);
	}

								/* frame selection */
	if ( FIRST < 0 && LAST < 0 )
		{
			firstframe = 1;
			LAST = INT_MAX;
				}
	else if ( FIRST < 0 && LAST > 0 )
		firstframe = 1;
	else 
		{
			firstframe = FIRST;
				
			if ( LAST < 0 )
				LAST = INT_MAX;
						}
	
	FIRST = firstframe;




#ifdef GRA					/* Graphics initialisation stuff */
	if ( GRAPHICS)
	{
        noborder();
        prefsize( WINSIZE, WINSIZE );
        winid = winopen( "Carma" );
        if ( winid == -1 )
                {
                        printf("\033[31m\033[1mNo more windows available ? Aborting.\033[0m\n");
                        myexit( 1 );
                                                }
        winset ( winid );
	ortho2( -GRABOX/2.0, GRABOX/2.0, -GRABOX/2.0, GRABOX/2.0);
	doublebuffer();
	gconfig();
        color(0);
        clear();
	mapcolor(255,80,80,80);
	YGL_INIT = YES;

	linewidth( LINEW );

	if ( GRADIENT )
	{
	int	red, green, blue;
	float	x, gamma;

	for (i=2 ; i <= 254 ; i++ )
		{
		x = (float)(i)/255.0;
		gamma = pow(x, (1/2.5)) / x;
		red = (int)(gamma * ((765*i)/255>255?255:(765*i)/255) + 0.50);
		green = (int)(gamma*(i<85?0:((765*(i-85))/255>255?255:(765*(i-85))/255)) + 0.50);
		blue = (int)(gamma*(i<170?0:((765*(i-170))/255>255?255:(765*(i-170))/255)) + 0.50);
		if ( red > 255 )
			red = 255;
		if ( blue > 255 )
			blue = 255;
		if ( green > 255 )
			green = 255;

		mapcolor( i, red, green, blue );

		}
	}
	else if ( CPK )
		{
					
			mapcolor( CARBONC   , 220, 220, 220);
			mapcolor( CALCIUMC  , 169, 169, 169);
			mapcolor( CHLORC    , 0, 255, 0);
			mapcolor( HYDROGENC , 80, 80, 80);
			mapcolor( NITROGENC , 0, 60, 255 );
			mapcolor( OXYGENC   , 255, 0, 0);
			mapcolor( PHOSPHOC  , 255, 165, 0);
			mapcolor( SULPHC    , 255, 255, 0);
			mapcolor( IRONC     , 255, 165, 0);
			mapcolor( SODC      , 255, 255, 0);
			mapcolor( MAGNC     , 34, 139, 34);
			mapcolor( ZINCC     ,165, 42, 42 );
			mapcolor( OTHERC    ,255, 20, 147 );

		}
	else
		{
			mapcolor( 2, 0, 255, 0 );
			mapcolor( 3, 255, 255, 0 );
			mapcolor( 4, 0, 0, 255 );
			mapcolor( 5, 255, 0, 255 );
			mapcolor( 6, 0, 255, 255 );
			mapcolor( 7, 255, 0, 0 );

			mapcolor( 8, 0, 170, 0 );
			mapcolor( 9, 170, 170, 0 );
			mapcolor( 10, 0, 0, 170 );
			mapcolor( 11, 170, 0, 170 );
			mapcolor( 12, 0, 170, 170 );
			mapcolor( 13, 170, 0, 0 );

			mapcolor( 14, 0, 85, 0 );
			mapcolor( 15, 85, 85, 0 );
			mapcolor( 16, 0, 0, 85 );
			mapcolor( 17, 85, 0, 85 );
			mapcolor( 18, 0, 85, 85 );
			mapcolor( 19, 85, 0, 0 );

		}

	}
#endif




								/* We will be reading the whole section as one large array */
								/* of floats, and we will then take care about the x,y,z */
								/* offsets in that table */
	
	
			
/*****************************************************************************************************************************/
/**   Produce distance maps for all selected frames (or, all frames)                                                        **/
/*****************************************************************************************************************************/
					
	if ( 	FIND_RMS == NO && FIND_COV == NO && DO_FIT == NO && CROSSDCD == NO &&
  		CALC_MAP == NO && GYRATION == NO && DPCA == NO && ASA == NO &&
		WRITE_PDB == NO )
	{	

#ifdef GRA
					/* With graphics on, just show the trajectory */
		if ( GRAPHICS )
		{

		if ( FIRST > 1 )
			if ( lseek( dcd, (off_t)(bytes_per_set * (off_t)(FIRST-1)), SEEK_CUR ) == (off_t)(-1) )
				{
					printf("\033[31m\033[1mRequested frame not present ? Abort.\033[0m\n");
					myexit(1);
							}

		start = lseek( dcd, (off_t)(0), SEEK_CUR );

		frame = firstframe;
		if ( VERBOSE )
		printf("Now processing frame %8d", frame);
		while( frame <= LAST )
		{
		if ( (unsigned int)(read( dcd, (void *)(&dcd_frame[1]), (size_t)(bytes_per_set) )) != bytes_per_set )
			{
				if ( LOOP )
				{
				if ( lseek( dcd, (off_t)(start), SEEK_SET ) == (off_t)(-1) )
					{
					printf("\033[31m\033[1mCan not seek back to the beginning of data ? Abort.\033[0m\n");
					myexit(1);
						}

				frame = firstframe;
				}
				else
				{
				if ( VERBOSE )
				printf("%8d", (frame-1) );
				if ( frame == FIRST )
					{
						printf("\033[31m\033[1m\nRequested frame not present ? Abort.\033[0m\n");
						myexit(1);
								}

#ifndef WINDOWS
				if ( VERBOSE )
					{
					end_timer = time(NULL);
					printf("\033[32m\033[1m\nEnd of DCD reached. All done in %1.1f minutes.\033[0m\n", (float)(end_timer-start_timer)/60.0 );
					}
#endif

				myexit(0);
						}
							}
		sprintf( framestring, "%d", frame );
		if ( (frame-firstframe) % STEP == 0 )
		{		
		build_CAs( (int)(nofatoms) + 2);
		}
		frame++;


		if ( VERBOSE )
		printf("%8d", frame );
		}	
		
		if ( frame == LAST+1 )
			{
				if ( VERBOSE )
				{
				printf("%8d", (frame-1) );
#ifndef WINDOWS				
				end_timer = time(NULL);
				printf("\033[32m\033[1m\nAll done in %1.1f minutes.\033[0m\n", (float)(end_timer-start_timer)/60.0);
#endif
				}
				myexit(0);
						}
		



		}
#endif


		/* Distance calcs */

		if ( DISTFIRST != -1 || DISTSECOND != -1 || HAVE_DISTANCE_FILE == YES )
		{
		FILE	*dist;
		FILE	*in;
		int	pairs[MAX_NOF_BACK][2];
		int	tot_dist = 0;
		int	at1, at2;
		char    string[300];
		
		if ( HAVE_DISTANCE_FILE == YES )
		{
			in= fopen( DIST_NAME, "r" );
			if ( in == NULL )
				{
        	                        printf("\033[31m\033[1mCan not open file to read distance pairs.\033[0m\n");
					myexit( 1 );
				}
			while ( fgets( string, 299, in ) != NULL )
			{
				if ( sscanf( string, "%d %d", &at1, &at2 ) == 2 )
				{
				at1--;
				at2--;
				if ( at1 < 0 || at2 < 0 || at1 > nofCAs || at2 > nofCAs )
					{
						printf("\033[31m\033[1mRequested atom index out of range. Abort.\033[0m\n");
						myexit(1);
								}
				pairs[tot_dist][0] = at1;
				pairs[tot_dist][1] = at2;
				tot_dist++;
				if ( tot_dist > MAX_NOF_BACK-2 )
					{
						printf("\033[31m\033[1mToo many atom pairs for distances. Increase MAX_NOF_BACK.\033[0m\n");
						myexit(1);
								}
				}
					
			}
			fclose( in );
			if ( VERBOSE )
			{
				printf("\033[32m\033[1mRead %d pairs for distance calculation.\033[0m\n", tot_dist );
			}
		}
		else
		{
		if ( DISTFIRST < 0 || DISTSECOND < 0 || DISTSECOND >= nofCAs || DISTFIRST >= nofCAs )
				{
					printf("\033[31m\033[1mRequested atom index out of range. Abort.\033[0m\n");
					myexit(1);
							}
		}
		
			
		dist = fopen("carma.distances", "w");
	        if ( dist == NULL )
        	        {
                		printf("\033[31m\033[1mCan not open file for writing distances. Abort.\n");
                		myexit(1);
                				}

		if ( FIRST > 1 )
			if ( lseek( dcd, (off_t)(bytes_per_set * (off_t)(FIRST-1)), SEEK_CUR ) == (off_t)(-1) )
				{
					printf("\033[31m\033[1mRequested frame not present ? Abort.\033[0m\n");
					myexit(1);
							}

		start = lseek( dcd, (off_t)(0), SEEK_CUR );

		frame = firstframe;
		if ( VERBOSE )
		printf("Now processing frame %8d", frame);
		while( frame <= LAST )
		{
		if ( (unsigned int)(read( dcd, (void *)(&dcd_frame[1]), (size_t)(bytes_per_set) )) != bytes_per_set )
			{
				if ( VERBOSE )
				printf("%8d", (frame-1) );
				if ( frame == FIRST )
					{
						printf("\033[31m\033[1m\nRequested frame not present ? Abort.\033[0m\n");
						myexit(1);
								}
#ifndef WINDOWS
				if ( VERBOSE )
					{
					end_timer = time(NULL);
					printf("\033[32m\033[1m\nEnd of DCD reached. All done in %1.1f minutes.\033[0m\n", (float)(end_timer-start_timer)/60.0 );
					}
#endif
				fclose(dist);
				myexit(0);
							}
		if ( (frame-firstframe) % STEP == 0 )
		{		
		build_CAs( (int)(nofatoms) + 2);

		if ( HAVE_DISTANCE_FILE == NO )
		{
		fprintf(dist, "% 7d % 9.4f\n", frame, sqrt( (CAs[DISTSECOND][0]-CAs[DISTFIRST][0])*(CAs[DISTSECOND][0]-CAs[DISTFIRST][0])+
						            (CAs[DISTSECOND][1]-CAs[DISTFIRST][1])*(CAs[DISTSECOND][1]-CAs[DISTFIRST][1])+
						            (CAs[DISTSECOND][2]-CAs[DISTFIRST][2])*(CAs[DISTSECOND][2]-CAs[DISTFIRST][2]) ) );
		}
		else
		{
		fprintf(dist, "% 7d", frame );

		for ( i=0 ; i < tot_dist ; i++ )
		{
			at1 = pairs[i][0];
			at2 = pairs[i][1];
			fprintf(dist, " % 9.4f", sqrt( (CAs[at2][0]-CAs[at1][0])*(CAs[at2][0]-CAs[at1][0])+
						       (CAs[at2][1]-CAs[at1][1])*(CAs[at2][1]-CAs[at1][1])+
						       (CAs[at2][2]-CAs[at1][2])*(CAs[at2][2]-CAs[at1][2]) ) );
			
		}
		fprintf(dist, "\n");
		}

		if ( STEP > 1 )
			{
				if ( lseek( dcd, (off_t)(bytes_per_set * (off_t)(STEP-1)), SEEK_CUR ) == (off_t)(-1) )
				{
					printf("\033[31m\033[1mRequested frame not present ? Abort.\033[0m\n");
					myexit(1);
							}
				frame += (STEP-1);
			}
			
		}
		frame++;


		if ( VERBOSE )
		printf("%8d", frame );
		}	
		
		if ( frame == LAST+1 )
			{
				if ( VERBOSE )
				{
				printf("%8d", (frame-1) );
#ifndef WINDOWS
				end_timer = time(NULL);
				printf("\033[32m\033[1m\nAll done in %1.1f minutes.\033[0m\n", (float)(end_timer-start_timer)/60.0 );
#endif
				}
				fclose(dist);
				myexit(0);
						}
		



		}






		/* Torsions ... */

		if ( TORSFIRST != -1 || TORSSECOND != -1 || TORSTHIRD != -1 || TORSFOURTH != -1 || HAVE_TORSION_FILE == YES )
		{
		FILE	*tors;
		FILE	*in;
		int	tetras[MAX_NOF_BACK][4];
		int	tot_tetras = 0;
		int	at1, at2, at3, at4;
		char    string[300];
		
		if ( HAVE_TORSION_FILE == YES )
		{
			in= fopen( TORS_NAME, "r" );
			if ( in == NULL )
				{
        	                        printf("\033[31m\033[1mCan not open file to read torsion tetraplets.\033[0m\n");
					myexit( 1 );
				}
			while ( fgets( string, 299, in ) != NULL )
			{
				if ( sscanf( string, "%d %d %d %d", &at1, &at2, &at3, &at4 ) == 4 )
				{
				at1--;
				at2--;
				at3--;
				at4--;
				if ( at1 < 0 || at2 < 0 || at3 < 0 || at4 < 0 || at1 > nofCAs || at2 > nofCAs || at3 > nofCAs || at4 > nofCAs )
					{
						printf("\033[31m\033[1mRequested atom index out of range. Abort.\033[0m\n");
						myexit(1);
								}
				tetras[tot_tetras][0] = at1;
				tetras[tot_tetras][1] = at2;
				tetras[tot_tetras][2] = at3;
				tetras[tot_tetras][3] = at4;
				tot_tetras++;
				if ( tot_tetras > MAX_NOF_BACK-2 )
					{
						printf("\033[31m\033[1mToo many atom tetraplets for torsions. Increase MAX_NOF_BACK.\033[0m\n");
						myexit(1);
								}
				}
					
			}
			fclose( in );
			if ( VERBOSE )
			{
				printf("\033[32m\033[1mRead %d tetraplets for torsion calculation.\033[0m\n", tot_tetras );
			}
		}
		else
		{
		if ( 	TORSFIRST  < 0 || TORSFIRST  >= nofCAs ||
			TORSSECOND < 0 || TORSSECOND >= nofCAs ||
			TORSTHIRD  < 0 || TORSTHIRD  >= nofCAs ||
			TORSFOURTH < 0 || TORSFOURTH >= nofCAs )
				{
					printf("\033[31m\033[1mRequested atom index out of range. Abort.\033[0m\n");
					myexit(1);
							}
		}

			
		tors = fopen("carma.torsions", "w");
	        if ( tors == NULL )
        	        {
                		printf("\033[31m\033[1mCan not open file for writing torsions. Abort.\n");
                		myexit(1);
                				}

		if ( FIRST > 1 )
			if ( lseek( dcd, (off_t)(bytes_per_set * (off_t)(FIRST-1)), SEEK_CUR ) == (off_t)(-1) )
				{
					printf("\033[31m\033[1mRequested frame not present ? Abort.\033[0m\n");
					myexit(1);
							}

		start = lseek( dcd, (off_t)(0), SEEK_CUR );

		frame = firstframe;
		if ( VERBOSE )
		printf("Now processing frame %8d", frame);
		while( frame <= LAST )
		{
		if ( (unsigned int)(read( dcd, (void *)(&dcd_frame[1]), (size_t)(bytes_per_set) )) != bytes_per_set )
			{
				if ( VERBOSE )
				printf("%8d", (frame-1) );
				if ( frame == FIRST )
					{
						printf("\033[31m\033[1m\nRequested frame not present ? Abort.\033[0m\n");
						myexit(1);
								}

#ifndef WINDOWS
				if ( VERBOSE )
					{
					end_timer = time(NULL);
					printf("\033[32m\033[1m\nEnd of DCD reached. All done in %1.1f minutes.\033[0m\n", (float)(end_timer-start_timer)/60.0 );
					}
#endif
				fclose(tors);
				myexit(0);
							}
		if ( (frame-firstframe) % STEP == 0 )
		{		
		build_CAs( (int)(nofatoms) + 2);
		


		if ( HAVE_TORSION_FILE == NO )
		{
		fprintf(tors, "% 9d %+9.4f\n", frame, torsion(
				CAs[TORSFIRST ][0], CAs[TORSFIRST ][1], CAs[TORSFIRST ][2],
				CAs[TORSSECOND][0], CAs[TORSSECOND][1], CAs[TORSSECOND][2],
				CAs[TORSTHIRD ][0], CAs[TORSTHIRD ][1], CAs[TORSTHIRD ][2],
				CAs[TORSFOURTH][0], CAs[TORSFOURTH][1], CAs[TORSFOURTH][2] ) );
		}
		else
		{
		fprintf(tors, "% 9d", frame );
		
		for ( i=0 ; i < tot_tetras ; i++ )
		{
			at1 = tetras[i][0];
			at2 = tetras[i][1];
			at3 = tetras[i][2];
			at4 = tetras[i][3];
			fprintf(tors, " %+9.4f", torsion(
					CAs[at1][0], CAs[at1][1], CAs[at1][2],
					CAs[at2][0], CAs[at2][1], CAs[at2][2],
					CAs[at3][0], CAs[at3][1], CAs[at3][2],
					CAs[at4][0], CAs[at4][1], CAs[at4][2] ) );
			
		}
		fprintf(tors, "\n");
		
		}
		
		
		if ( STEP > 1 )
			{
				if ( lseek( dcd, (off_t)(bytes_per_set * (off_t)(STEP-1)), SEEK_CUR ) == (off_t)(-1) )
				{
					printf("\033[31m\033[1mRequested frame not present ? Abort.\033[0m\n");
					myexit(1);
							}
				frame += (STEP-1);
			}

		}
		frame++;


		if ( VERBOSE )
		printf("%8d", frame );
		}	
		
		if ( frame == LAST+1 )
			{
				if ( VERBOSE )
				{
				printf("%8d", (frame-1) );
#ifndef WINDOWS
				end_timer = time(NULL);
				printf("\033[32m\033[1m\nAll done in %1.1f minutes.\033[0m\n", (float)(end_timer-start_timer)/60.0 );
#endif
				}
				fclose(tors);
				myexit(0);
						}
		



		}



		/* Bending angles... */

		if ( BENDFIRST != -1 || BENDSECOND != -1 || BENDTHIRD != -1 || HAVE_BEND_FILE == YES )
		{
		FILE	*bend;
		FILE	*in;
		int	triplets[MAX_NOF_BACK][3];
		int	tot_triplets = 0;
		int	at1, at2, at3;
		char    string[300];
		
		if ( HAVE_BEND_FILE == YES )
		{
			in= fopen( BEND_NAME, "r" );
			if ( in == NULL )
				{
        	                        printf("\033[31m\033[1mCan not open file to read triplets for bending angles.\033[0m\n");
					myexit( 1 );
				}
			while ( fgets( string, 299, in ) != NULL )
			{
				if ( sscanf( string, "%d %d %d", &at1, &at2, &at3 ) == 3 )
				{
				at1--;
				at2--;
				at3--;
				if ( at1 < 0 || at2 < 0 || at3 < 0 || at1 > nofCAs || at2 > nofCAs || at3 > nofCAs )
					{
						printf("\033[31m\033[1mRequested atom index out of range. Abort.\033[0m\n");
						myexit(1);
								}
				triplets[tot_triplets][0] = at1;
				triplets[tot_triplets][1] = at2;
				triplets[tot_triplets][2] = at3;
				tot_triplets++;
				if ( tot_triplets > MAX_NOF_BACK-2 )
					{
						printf("\033[31m\033[1mToo many atom triplets for angles. Increase MAX_NOF_BACK.\033[0m\n");
						myexit(1);
								}
				}
					
			}
			fclose( in );
			if ( VERBOSE )
			{
				printf("\033[32m\033[1mRead %d triplets for bending angles' calculation.\033[0m\n", tot_triplets );
			}
		}
		else
		{
		if ( 	BENDFIRST  < 0 || BENDFIRST  >= nofCAs ||
			BENDSECOND < 0 || BENDSECOND >= nofCAs ||
			BENDTHIRD  < 0 || BENDTHIRD  >= nofCAs )
				{
					printf("\033[31m\033[1mRequested atom index out of range. Abort.\033[0m\n");
					myexit(1);
							}
		}
			
		bend = fopen("carma.bendangles", "w");
	        if ( bend == NULL )
        	        {
                		printf("\033[31m\033[1mCan not open file for writing bending angles. Abort.\n");
                		myexit(1);
                				}

		if ( FIRST > 1 )
			if ( lseek( dcd, (off_t)(bytes_per_set * (off_t)(FIRST-1)), SEEK_CUR ) == (off_t)(-1) )
				{
					printf("\033[31m\033[1mRequested frame not present ? Abort.\033[0m\n");
					myexit(1);
							}

		start = lseek( dcd, (off_t)(0), SEEK_CUR );

		frame = firstframe;
		if ( VERBOSE )
		printf("Now processing frame %8d", frame);
		while( frame <= LAST )
		{
		if ( (unsigned int)(read( dcd, (void *)(&dcd_frame[1]), (size_t)(bytes_per_set) )) != bytes_per_set )
			{
				if ( VERBOSE )
				printf("%8d", (frame-1) );
				if ( frame == FIRST )
					{
						printf("\033[31m\033[1m\nRequested frame not present ? Abort.\033[0m\n");
						myexit(1);
								}
#ifndef WINDOWS
				if ( VERBOSE )
				{
				end_timer = time(NULL);
				printf("\033[32m\033[1m\nEnd of DCD reached. All done in %1.1f minutes.\033[0m\n", (float)(end_timer-start_timer)/60.0);
				}
#endif
				fclose(bend);
				myexit(0);
							}
		if ( (frame-firstframe) % STEP == 0 )
		{		
		build_CAs( (int)(nofatoms) + 2);




		if ( HAVE_BEND_FILE == NO )
		{
		fprintf(bend, "% 9d %+9.4f\n", frame, bendangle(
				CAs[BENDFIRST ][0], CAs[BENDFIRST ][1], CAs[BENDFIRST ][2],
				CAs[BENDSECOND][0], CAs[BENDSECOND][1], CAs[BENDSECOND][2],
				CAs[BENDTHIRD ][0], CAs[BENDTHIRD ][1], CAs[BENDTHIRD ][2] ) );
		}
		else
		{
		fprintf(bend, "% 9d", frame );
		
		for ( i=0 ; i < tot_triplets ; i++ )
		{
			at1 = triplets[i][0];
			at2 = triplets[i][1];
			at3 = triplets[i][2];
			fprintf(bend, " %+9.4f", bendangle(
					CAs[at1][0], CAs[at1][1], CAs[at1][2],
					CAs[at2][0], CAs[at2][1], CAs[at2][2],
					CAs[at3][0], CAs[at3][1], CAs[at3][2] ) );
			
		}
		fprintf(bend, "\n");
		
		}


		if ( STEP > 1 )
			{
				if ( lseek( dcd, (off_t)(bytes_per_set * (off_t)(STEP-1)), SEEK_CUR ) == (off_t)(-1) )
				{
					printf("\033[31m\033[1mRequested frame not present ? Abort.\033[0m\n");
					myexit(1);
							}
				frame += (STEP-1);
			}

		}
		frame++;


		if ( VERBOSE )
		printf("%8d", frame );
		}	
		
		if ( frame == LAST+1 )
			{
				if ( VERBOSE )
				{
				printf("%8d", (frame-1) );
#ifndef WINDOWS
				end_timer = time(NULL);
				printf("\033[32m\033[1m\nAll done in %1.1f minutes.\033[0m\n", (float)(end_timer-start_timer)/60.0 );
#endif
				}
				fclose(bend);
				myexit(0);
						}
		



		}



		/* RMS ... */


		D1 = matrix( 1, nofCAs, 1, nofCAs);
		if ( QFRACTION == YES )
			{
				Dref = matrix( 1, nofCAs, 1, nofCAs);
				HAVE_REF = NO;
				q_file = fopen("carma.Qfraction.dat", "w" );
				if ( q_file == NULL )
					{
						printf("\033[31m\033[1mCan not open carma.Qfraction.dat for writing. Abort.\033[0m\n");
						myexit(1);
					}
				
			}


		if ( QFRACTION == NO  &&  ((float)(min2(headerframes, LAST)) - firstframe +1.0)/(float)(STEP) > 100.0 )
			{
			printf("\033[31m\033[1mIf the DCD header is correct, this will create %d postscript files.\033[0m\n", 
					(int)(((float)(min2(headerframes, LAST)) - firstframe +1.0)/(float)(STEP)) );
#ifndef WINDOWS
			sleep(2);
#endif
			}
			

		if ( FIRST > 1 )
			if ( lseek( dcd, (off_t)(bytes_per_set * (off_t)(FIRST-1)), SEEK_CUR ) == (off_t)(-1) )
				{
					printf("\033[31m\033[1mRequested frame not present ? Abort.\033[0m\n");
					myexit(1);
							}

		frame = firstframe;
		if ( VERBOSE && QFRACTION == NO )
		printf("Now processing frame %8d", frame);
		while( frame <= LAST )
		{
		if ( (unsigned int)(read( dcd, (void *)(&dcd_frame[1]), (size_t)(bytes_per_set) )) != bytes_per_set )
			{
				if ( VERBOSE )
				printf("%8d", (frame-1) );
				if ( frame == FIRST )
					{
						printf("\033[31m\033[1m\nRequested frame not present ? Abort.\033[0m\n");
						myexit(1);
								}
#ifndef WINDOWS
				if ( VERBOSE )
				{
				end_timer = time(NULL);
				printf("\033[32m\033[1m\nEnd of DCD reached. All done in %1.1f minutes.\033[0m\n", (float)(end_timer-start_timer)/60.0 );
				}
#endif
				myexit(0);
						}

		sprintf( framestring, "%d", frame );
		if ( (frame-firstframe) % STEP == 0 )
		{		
		build_CAs( (int)(nofatoms) + 2);
		max = Dist();
		
		if ( QFRACTION == YES && HAVE_REF == NO )
			{
				for ( i=1 ; i <= nofCAs ; i++ )
				for ( k=1 ; k <= nofCAs ; k++ )
					Dref[i][k] = D1[i][k];


				for ( i=1 ; i <= nofCAs ; i++ )
				for ( k=i ; k <= nofCAs ; k++ )
					if ( strcmp( str_segname[i-1], str_segname[k-1] ) != 0 )
						{							
						printf("\033[31m\033[1m\nCalculation of fraction of native contacts only supported for a single chain.\033[0m\n\n");
						myexit(1);
						}

				tot_for_qsfraction = 0;
				for ( i=1 ; i <= nofCAs ; i++ )
				for ( k=i ; k <= nofCAs ; k++ )
					if ( abs( str_resid[i-1] - str_resid[k-1] ) > Q_SEPARATION && Dref[i][k] <= Q_CUTOFF )
						{
							tot_for_qsfraction++;
						}


				tot_for_sfraction = 0;
				for ( i=1 ; i <= nofCAs ; i++ )
				for ( k=i ; k <= nofCAs ; k++ )
					if ( abs( str_resid[i-1] - str_resid[k-1] ) > Q_SEPARATION )
						{
							tot_for_sfraction++;
						}

                                tot_for_qfraction = 0;
                                for ( i=1 ; i <= nofCAs ; i++ )
                                for ( k=i ; k <= nofCAs ; k++ )
                                        if ( abs( str_resid[i-1] - str_resid[k-1] ) > Q_SEPARATION && Dref[i][k] <= Q_CUTOFF )
                                                {
                                                        tot_for_qfraction++;
						}

				if ( tot_for_qfraction < 2 || tot_for_qsfraction < 2 )
					{							
					printf("\033[31m\033[1m\nOnly %d distances entered the calculation of native contacts ? Abort.\033[0m\n\n", tot_for_qfraction);
					myexit(1);
					}

				printf("\033[33m%d pairs entered the calculation of the fraction of native contacts.\n\033[0m", tot_for_qfraction );
				printf("\033[33m%d pairs entered the calculation of the fraction of the similarity measure.\n\033[0m", tot_for_sfraction );
				printf("Now processing frame %8d", frame);
				
				HAVE_REF = YES;
			}
		
		
		
		if ( QFRACTION == YES )
			{
				double	countqs = 0.0;
				double	counts = 0.0;
				int	count = 0;
				
				for ( i=1 ; i <= nofCAs ; i++ )
				for ( k=i ; k <= nofCAs ; k++ )
					{
					if ( abs( str_resid[i-1] - str_resid[k-1] ) > Q_SEPARATION )
						counts += exp( -( D1[i][k] - Dref[i][k]) * ( D1[i][k] - Dref[i][k]) / pow( fabs( (float)(str_resid[i-1] - str_resid[k-1])), 0.30 ) );

					if ( abs( str_resid[i-1] - str_resid[k-1] ) > Q_SEPARATION && D1[i][k] <= Q_CUTOFF && Dref[i][k] <= Q_CUTOFF )
						countqs += exp( -( D1[i][k] - Dref[i][k]) * ( D1[i][k] - Dref[i][k]) / pow( fabs( (float)(str_resid[i-1] - str_resid[k-1])), 0.30 ) );

					if ( abs( str_resid[i-1] - str_resid[k-1] ) > Q_SEPARATION && D1[i][k] <= Q_CUTOFF && Dref[i][k] <= Q_CUTOFF )
						count++;
					}

				counts /= tot_for_sfraction;
				countqs /= tot_for_qsfraction;
				
				fprintf(q_file, "% 7d % 6.4f % 6.4f % 6.4f\n", frame, (float)(count) / tot_for_qfraction, (float)(countqs), (float)(counts) );
			}
		else
		{
		if ( HAVE_MIN == NO )
			gmin = 0.0;
		if ( HAVE_MAX == NO )
			gmax = max;
		sprintf( frameno, ".%07d", frame );
		strcpy( filename, strrchr( argv[HAVE_DCD], '/') != NULL ? strrchr( argv[HAVE_DCD], '/') + 1 : argv[HAVE_DCD] );
		strcat( filename, frameno );
		if ( VERBOSE )
			{
				VERBOSE = NO;
				wps( D1, filename );
				VERBOSE = YES;
			}
		else
			wps( D1, filename );
		}
			

		if ( STEP > 1 )
			{
				if ( lseek( dcd, (off_t)(bytes_per_set * (off_t)(STEP-1)), SEEK_CUR ) == (off_t)(-1) )
				{
					printf("\033[31m\033[1mRequested frame not present ? Abort.\033[0m\n");
					myexit(1);
							}
				frame += (STEP-1);
			}

		}
		frame++;
		if ( VERBOSE )
		printf("%8d", frame );
		}	


		
		if ( frame == LAST+1 )
			{
				if ( VERBOSE )
				{
				printf("%8d", (frame-1) );
#ifndef WINDOWS
				end_timer = time(NULL);
				printf("\033[32m\033[1m\nAll done in %1.1f minutes.\033[0m\n", (float)(end_timer-start_timer)/60.0 );
#endif
				}
				myexit(0);
						}
		
		
		
	}



/*****************************************************************************************************************************/
/**	This is the water and ions distribution staff 									    **/
/*****************************************************************************************************************************/

	if ( CALC_MAP == YES )
	{
	int	gridx;
	int	gridy;
	int 	gridz;
	int	gx, gy, gz;
	float	***map;
	float	***cmap;
	float	*pmap;
	FILE	*cns;
	float	mapaver;
	float	mapsigma;
	float	frac_x, frac_y, frac_z;
	int	ATOMS_OUTSIDE = 0;
	

	/* Decide grid size */
	if ( CRYSTALLOGRAPHIC_FRAME )
		{
			gridx = cryst_x;
			gridy = cryst_y;
			gridz = cryst_z;
		}
	else
		{
			gridx = (int)((Xmax-Xmin)/Grid+0.50);
			gridy = (int)((Ymax-Ymin)/Grid+0.50);
			gridz = (int)((Zmax-Zmin)/Grid+0.50);
		}
		
		
	map = f3tensor( 1, gridx, 1, gridy, 1, gridz);
	if ( VERBOSE )
		printf("Allocated map file %d %d %d\n", gridx, gridy, gridz );


	/* Initialise it */	
	pmap = &map[1][1][1];
	for ( i=0 ; i < gridx*gridy*gridz ; i++ )
		pmap[i] = 0.0;


	/* Rock ... */
	if ( FIRST > 1 )
		if ( lseek( dcd, (off_t)(bytes_per_set * (off_t)(FIRST-1)), SEEK_CUR ) == (off_t)(-1) )
			{
				printf("\033[31m\033[1mRequested frame not present ? Abort.\033[0m\n");
				myexit(1);
						}
						

						/* Mark current position */
	start = lseek( dcd, (off_t)(0), SEEK_CUR );

	entered = 0;
	frame = firstframe;
	if ( VERBOSE )
	printf("Now processing frame %8d", frame);
	while( frame <= LAST )
		{
		if ( (unsigned int)(read( dcd, (void *)(&dcd_frame[1]), (size_t)(bytes_per_set) )) != bytes_per_set )
			{
				if ( VERBOSE )
				printf("%8d", (frame-1) );
				if ( frame == FIRST )
					{
						printf("\033[31m\033[1m\nRequested frame not present ? Abort.\033[0m\n");
						myexit(1);
								}
				if ( VERBOSE )
				printf("\nEnd of DCD reached. Write map.\n");
				break;
									}

		sprintf( framestring, "%d", frame );

		if ( (frame-firstframe) % STEP == 0 )
		{		
		entered++;		
		build_CAs( (int)(nofatoms) + 2);


		if ( CRYSTALLOGRAPHIC_FRAME )
		{
		for ( i=0 ; i < nofCAs ; i++ )
			{						/* Ortho to fractional */
				frac_x = f2o_11*CAs[i][0] + f2o_12*CAs[i][1] + f2o_13*CAs[i][2] + f2o_14;
				frac_y = f2o_21*CAs[i][0] + f2o_22*CAs[i][1] + f2o_23*CAs[i][2] + f2o_24;
				frac_z = f2o_31*CAs[i][0] + f2o_32*CAs[i][1] + f2o_33*CAs[i][2] + f2o_34;
				gx = nearint(gridx * frac_x);
				gy = nearint(gridy * frac_y);
				gz = nearint(gridz * frac_z);

				/* printf("% 8.4f % 8.4f % 8.4f % 4d % 4d % 4d\n", frac_x, frac_y, frac_z, gx, gy, gz ); */

				if ( gx == gridx )
					gx = 0;
				if ( gy == gridy )
					gy = 0;
				if ( gz == gridz )
					gz = 0;

				if ( gx < 0 || gx > gridx || gy < 0 || gy > gridy || gz < 0 || gz > gridz )
					{	
						ATOMS_OUTSIDE++;
						/* printf("% 8.4f % 8.4f % 8.4f % 4d % 4d % 4d\n", frac_x, frac_y, frac_z, gx, gy, gz );  */

						if ( gx < 0 ) 
							gx += gridx;
						if ( gy < 0 ) 
							gy += gridy;
						if ( gz < 0 ) 
							gz += gridz;
						if ( gx > gridx )
							gx -= gridx;
						if ( gy > gridy )                    
							gy -= gridy;
						if ( gz > gridz )                    
							gz -= gridz;

					}
				if ( MASSES == YES )
					map[gx+1][gy+1][gz+1] += masses[i];
				else				
					map[gx+1][gy+1][gz+1] += 1.0;
			}		
		}
		else
		{
		for ( i=0 ; i < nofCAs ; i++ )
			{
				gx = (int)(gridx * (CAs[i][0] - Xmin) / (Xmax-Xmin) + 0.50) + 1;
				gy = (int)(gridy * (CAs[i][1] - Ymin) / (Ymax-Ymin) + 0.50) + 1;
				gz = (int)(gridz * (CAs[i][2] - Zmin) / (Zmax-Zmin) + 0.50) + 1;

				if ( gx >= 1 && gx <= gridx && gy >= 1 && gy <= gridy && gz >= 1 && gz <= gridz )
					map[gx][gy][gz] += 1.0;
						}
		}
		
		

		if ( STEP > 1 )
			{
				if ( lseek( dcd, (off_t)(bytes_per_set * (off_t)(STEP-1)), SEEK_CUR ) == (off_t)(-1) )
				{
					printf("\033[31m\033[1mRequested frame not present ? Abort.\033[0m\n");
					myexit(1);
							}
				frame += (STEP-1);
			}
		}
		frame++;
		if ( VERBOSE )
		printf("%8d", frame );


						}

	if ( frame == LAST+1 )
		{
		if ( VERBOSE )
		printf("%8d\n", (frame-1) );
		}

	totentered = entered;
	if ( VERBOSE )						
	printf("%d frames entered the calculation.\n", entered );



	if ( SIGMOIDAL == YES )
	{
		if ( VERBOSE )
			printf("\033[33mTaking the logarithm base %f of the distribution.\033[0m\n", LAMBDA );
	
		for ( i=0 ; i < gridx*gridy*gridz ; i++ )
			{
				if ( pmap[i] > 0 )
					pmap[i] =  log( pmap[i] ) / log( LAMBDA );
			}
	}
	

	max = 0.0;
	mapaver = 0.0;
	mapsigma = 0.0;
	for ( i=0 ; i < gridx*gridy*gridz ; i++ )
		{
			if ( pmap[i] > max )
				max =  pmap[i];
			mapaver += pmap[i];
						}

	mapaver /= (float)(gridx*gridy*gridz);
	for ( i=0 ; i < gridx*gridy*gridz ; i++ )
		mapsigma += (pmap[i]-mapaver)*(pmap[i]-mapaver);

	mapsigma = sqrt( mapsigma / (float)(gridx*gridy*gridz));


	if ( VERBOSE )
		{
			printf("Maximum count recorded is %f\n", max );
			printf("Map average and sigma are %f and %f\n", mapaver, mapsigma );
		}
		

	sprintf( frameno, ".map");
	strcpy( filename, strrchr( argv[HAVE_DCD], '/') != NULL ? strrchr( argv[HAVE_DCD], '/') + 1 : argv[HAVE_DCD] );
	strcat( filename, frameno );

	cns = fopen( filename, "w");
        if ( cns == NULL )
                {
                printf("\033[31m\033[1mCan not open map file for writing. Abort.\n");
                myexit(1);
                }

	fprintf(cns, "\n");
	fprintf(cns, "       2\n");
	fprintf(cns, " REMARKS FILENAME=\"%s\"\n", filename);
	fprintf(cns, " REMARKS Created by Carma\n");
	
	if ( CRYSTALLOGRAPHIC_FRAME )
	{
	fprintf(cns, "%7d %7d %7d %7d %7d %7d %7d %7d %7d\n", gridx, 0, gridx-1, gridy, 0, gridy-1,gridz, 0, gridz-1 );
	fprintf(cns, "%7.5E %7.5E %7.5E %7.5E %7.5E %7.5E\n", cell_a, cell_b, cell_c, cell_alpha, cell_beta, cell_gamma );
	}
	else
	{	
	fprintf(cns, "%7d %7d %7d %7d %7d %7d %7d %7d %7d\n", gridx, (int)(Xmin*gridx/(Xmax-Xmin)), (int)(Xmax*gridx/(Xmax-Xmin)-1),
							gridy, (int)(Ymin*gridy/(Ymax-Ymin)), (int)(Ymax*gridy/(Ymax-Ymin)-1),
							gridz, (int)(Zmin*gridz/(Zmax-Zmin)), (int)(Zmax*gridz/(Zmax-Zmin)-1) );
	fprintf(cns, "%7.5E %7.5E %7.5E %7.5E %7.5E %7.5E\n", Xmax-Xmin, Ymax-Ymin, Zmax-Zmin, 90.0, 90.0, 90.0 );
	}
	fprintf(cns, "ZYX\n");
	for (gz=1 ; gz <= gridz ; gz ++)
	{
	i = 0;
	fprintf(cns, "%8d\n", gz-1 );
	for (gy=1 ; gy <= gridy ; gy ++)
	for (gx=1 ; gx <= gridx ; gx ++)
		{
			fprintf(cns, "%+8.5E", map[gx][gy][gz] );
			i++;
			if ( i == 6 )
				{
					i = 0;
					fprintf(cns, "\n");
				}
		}

	if ( i != 0 )
		fprintf(cns, "\n");

	}
	
	fprintf(cns, "   -9999\n");

	fprintf(cns, "%12.4E%12.4E\n", mapaver, mapsigma );

	fclose(cns);


							/* NA4 FORMAT MAP */
	if ( CRYSTALLOGRAPHIC_FRAME )
		{
			int     iuvw[3];
			float	cell[6];
			
			
			cmap = f3tensor( 1, gridy, 1, gridx, 1, gridz);

			for (gz=1 ; gz <= gridz ; gz ++)
			for (gy=1 ; gy <= gridy ; gy ++)
			for (gx=1 ; gx <= gridx ; gx ++)
				cmap[gy][gx][gz] = map[gx][gy][gz];
			

			iuvw[0] = 3;
			iuvw[1] = 1;
			iuvw[2] = 2;
			cell[0] = cell_a;
			cell[1] = cell_b;
			cell[2] = cell_c;
			cell[3] = cell_alpha;
			cell[4] = cell_beta;
			cell[5] = cell_gamma;
			
			sprintf( frameno, ".na4");
			strcpy( filename, strrchr( argv[HAVE_DCD], '/') != NULL ? strrchr( argv[HAVE_DCD], '/') + 1 : argv[HAVE_DCD] );
			strcat( filename, frameno );
				
			write_map( &filename[0], cmap, gridy, gridx, gridz, iuvw, 2, "Produced from carma v.1.2", cell );
		}
	
	
	
	if ( VERBOSE && ATOMS_OUTSIDE > 0 )
		printf("\033[31m\033[1m\nAtoms outside unit cell detected %d times.\033[0m\n", ATOMS_OUTSIDE);
	
	myexit(0);
	}





/*****************************************************************************************************************************/
/**	This is the CA-CA average and RMSD calculation									    **/
/*****************************************************************************************************************************/



	if ( FIND_RMS == YES )
	{
/*****************************************************************************************************************************/
/**   Calculate an average contact map (which will be used to calculate a rmsd map)                                         **/
/*****************************************************************************************************************************/


	for (i=0 ; i < 1000 ; i++ )			/* For pair distance distribution */
		pddf[i] = 0.0;


							/* D2 will be the "average" map */
							/* D3 will be the "rmsd" map */
	D1 = matrix( 1, nofCAs, 1, nofCAs);
	D2 = matrix( 1, nofCAs, 1, nofCAs);
	D3 = matrix( 1, nofCAs, 1, nofCAs);
	pD1 = &D1[1][1];
	pD2 = &D2[1][1];
	pD3 = &D3[1][1];
	for ( i=0 ; i < nofCAs*nofCAs ; i++ )
		{
			pD2[i] = 0.0;
			pD3[i] = 0.0;
					}

	if ( VERBOSE )
	printf("First pass to determine average map\n");

	if ( FIRST > 1 )
		if ( lseek( dcd, (off_t)(bytes_per_set * (off_t)(FIRST-1)), SEEK_CUR ) == (off_t)(-1) )
			{
				printf("\033[31m\033[1mRequested frame not present ? Abort.\033[0m\n");
				myexit(1);
						}
						

						/* Mark current position */
	start = lseek( dcd, (off_t)(0), SEEK_CUR );

	entered = 0;
	frame = firstframe;
	if ( VERBOSE )
	printf("Now processing frame %8d", frame);
	while( frame <= LAST )
		{
		if ( (unsigned int)(read( dcd, (void *)(&dcd_frame[1]), (size_t)(bytes_per_set) )) != bytes_per_set )
			{
				if ( VERBOSE )
				printf("%8d", (frame-1) );
				if ( frame == FIRST )
					{
						printf("\033[31m\033[1m\nRequested frame not present ? Abort.\033[0m\n");
						myexit(1);
								}
				if ( VERBOSE )
				printf("\nEnd of DCD reached. Write average map.\n");
				break;
									}

		sprintf( framestring, "%d", frame );

		if ( (frame-firstframe) % STEP == 0 )
		{		
		entered++;		
		build_CAs( (int)(nofatoms) + 2);
		max = Dist();

		for ( i=0 ; i < nofCAs*nofCAs ; i++ )
			pD2[i] += pD1[i];

		if ( STEP > 1 )
			{
				if ( lseek( dcd, (off_t)(bytes_per_set * (off_t)(STEP-1)), SEEK_CUR ) == (off_t)(-1) )
				{
					printf("\033[31m\033[1mRequested frame not present ? Abort.\033[0m\n");
					myexit(1);
							}
				frame += (STEP-1);
			}
		}
		frame++;
		if ( VERBOSE )
		printf("%8d", frame );


						}

	if ( frame == LAST+1 )
		{
		if ( VERBOSE )
		printf("%8d\n", (frame-1) );
		}
							/* D3 will hold the mean values for second pass */
	totentered = entered;
	if ( VERBOSE )						
	printf("%d frames entered the calculation.\n", entered );


	if ( PDDF == YES )
	{
	FILE	*pddf_file;	

	if ( VERBOSE )
		printf("Writing out mass-weighted pair distance distribution.\n");
		
	pddf_file = fopen("carma.pddf.dat", "w");
	if ( pddf_file == NULL )
	  {
	    printf("\033[31m\033[1mCan not open file for writing pair distance distribution. Abort.\n");
	    myexit(1);
	  }
	
	for( i=0 ; i < 1000 ; i++) 
		fprintf(pddf_file, " %15.4f %15.10e\n", i*PDDF_STEP + PDDF_STEP/2, pddf[i] );

	fclose( pddf_file );
	}


	max = 0.0;
	for ( i=0 ; i < nofCAs*nofCAs ; i++ )
		{
			pD2[i] /= (float)(entered);
			if ( pD2[i] > max )
				max =  pD2[i];
			pD3[i] = pD2[i];
						}
	if ( VERBOSE )
	printf("Maximum of observed average distances is %f\n", max );
	if ( HAVE_MIN == NO )
		gmin = 0.0;
	if ( HAVE_MAX == NO )
		gmax = max;
		
	sprintf( frameno, ".averag");
	strcpy( filename, strrchr( argv[HAVE_DCD], '/') != NULL ? strrchr( argv[HAVE_DCD], '/') + 1 : argv[HAVE_DCD] );
	strcat( filename, frameno );
	wps( D2, filename );


	

/*****************************************************************************************************************************/
/**   Second pass for rmsds ...                                                                                             **/
/*****************************************************************************************************************************/



	if ( lseek( dcd, (off_t)(start), SEEK_SET ) == (off_t)(-1) )
		{
			printf("\033[31m\033[1mCan not seek back to the beginning of data ? Abort.\033[0m\n");
			myexit(1);
					}


	for ( i=0 ; i < nofCAs*nofCAs ; i++ )
		pD2[i] = 0.0;

	if ( VERBOSE )
	printf("Second pass to calculate rmsd map ...\n");

	entered = 0;
	frame = firstframe;
	if ( VERBOSE )
	printf("Now processing frame %8d", frame);
	while( frame <= LAST )
		{
		if ( (unsigned int)(read( dcd, (void *)(&dcd_frame[1]), (size_t)(bytes_per_set) )) != bytes_per_set )
			{
				if ( VERBOSE )
				printf("%8d", (frame-1) );
				if ( frame == FIRST )
					{
						if ( VERBOSE )
						printf("\033[31m\033[1m\nRequested frame not present ? Abort.\033[0m\n");
						myexit(1);
								}
				if ( VERBOSE )
				printf("\nEnd of DCD reached. Write rmsd map.\n");
				break;
									}
				
		sprintf( framestring, "%d", frame );

		if ( (frame-firstframe) % STEP == 0 )
		{		
		entered++;		
		build_CAs( (int)(nofatoms) + 2);
		max = Dist();

		for ( i=0 ; i < nofCAs*nofCAs ; i++ )
			{
				v1 = pD1[i];
				v2 = pD3[i];
				pD2[i] += v1*v1 + v2*v2 - 2.00*v1*v2;
							}

		if ( STEP > 1 )
			{
				if ( lseek( dcd, (off_t)(bytes_per_set * (off_t)(STEP-1)), SEEK_CUR ) == (off_t)(-1) )
				{
					printf("\033[31m\033[1mRequested frame not present ? Abort.\033[0m\n");
					myexit(1);
							}
				frame += (STEP-1);
			}
		}
		frame++;
		if ( VERBOSE )
		printf("%8d", frame );


						}

	if ( frame == LAST+1 && VERBOSE )
		printf("%8d\n", (frame-1) );

	totentered = entered;						
	if ( VERBOSE )
	printf("%d frames entered the calculation.\n", entered );
	max = 0.0 ;
	for ( i=0 ; i < nofCAs*nofCAs ; i++ )
		{
			pD2[i] = sqrt( pD2[i] / (float)(entered));
			if ( pD2[i] > max )
				max =  pD2[i];

						}
	
	if ( VERBOSE )
	printf("Maximum rms deviation from average distances is %f\n", max );
	REVERSE = !REVERSE ;
	if ( HAVE_MIN == NO )
		gmin = 0.0;
	if ( MAX_RMSD <= 0.0 )
		gmax = max;
	else
		gmax = MAX_RMSD;	
		
	sprintf( frameno, ".rmsdev");
	strcpy( filename, strrchr( argv[HAVE_DCD], '/') != NULL ? strrchr( argv[HAVE_DCD], '/') + 1 : argv[HAVE_DCD] );
	strcat( filename, frameno );
	wps( D2, filename );

	myexit(0);
	}
	
	









/*****************************************************************************************************************************/
/**	'FIT' Keyword 													    **/
/*****************************************************************************************************************************/



	if ( DO_FIT == YES )
	{	
	float		*REF_xyz;
	float		*FIT_xyz;
	int		outdcd;
	char		*outdcdhead;
	float		current_rms;
	rotate_t 	rot_matrix;
	xlate_t		trans_matrix;
	FILE		*rms_evolution;

	int		gridx = 0;		/* For fmap */
	int		gridy = 0;
	int 		gridz = 0;
	int		gx, gy, gz;
	float		***map = 0;
	float		*pmap = 0;
	FILE		*cns;
	float		mapaver;
	float		mapsigma;
	FILE		*fmap_index;
	int		fmapindeces[MAX_NOF_CAS];
	int		fmap_nofatoms = 0;
	char		string[300];	




	if ( FAST_MAP )
	{
		
	fmap_index = fopen( "fmap.index", "r");
        if ( fmap_index == NULL )
                {
                printf("\033[31m\033[1mCan not open the \"fmap.index\" index file for reading. Abort.\n");
                myexit(1);
                }

	i = 0;

        while ( fgets( string, 299, fmap_index ) != NULL )
		{
			if ( sscanf( string, "%d", &fmapindeces[i]) != 1 )
				{	
					printf("\033[31m\033[1mThe 'fmap.index' file is not valid. Abort.\033[0m\n");
					myexit(1);
							}
			fmapindeces[i] = fmapindeces[i] - 1;
			if ( fmapindeces[i] < 0 )
				{
					printf("\033[31m\033[1mNOTE : carma expects 1-based indeces in the fmap.index file.\033[0m\n");
					myexit(1);
							}

			if ( fmapindeces[i] < 0 )
				{	
					printf("\033[31m\033[1mNegative index in the 'fmap.index' file ? Abort.\033[0m\n");
					myexit(1);
							}

			i++;
		}
	fmap_nofatoms = i;
	fclose( fmap_index );

	if ( VERBOSE )
		printf("Will produce a distribution map.\n");

	/* Decide grid size */
	gridx = (int)((Xmax-Xmin)/Grid+0.50);
	gridy = (int)((Ymax-Ymin)/Grid+0.50);
	gridz = (int)((Zmax-Zmin)/Grid+0.50);

	/* Allocate map */
	map = f3tensor( 1, gridx, 1, gridy, 1, gridz);
	if ( VERBOSE )
		printf("Allocated map file %d %d %d\n", gridx, gridy, gridz );


	/* Initialise it */	
	pmap = &map[1][1][1];
	for ( i=0 ; i < gridx*gridy*gridz ; i++ )
		pmap[i] = 0.0;

	}






	
	afterheader = lseek( dcd, (off_t)(0), SEEK_CUR );

	if ( VERBOSE )
		printf("Fit DCD frames onto reference frame.\n");

	if ( FIRST > 1 )
		if ( lseek( dcd, (off_t)(bytes_per_set * (off_t)(FIRST-1)), SEEK_CUR ) == (off_t)(-1) )
			{
				printf("\033[31m\033[1mRequested frame not present ? Abort.\033[0m\n");
				myexit(1);
						}


						/* Mark current position */
	start = lseek( dcd, (off_t)(0), SEEK_CUR );

	if ( lseek( dcd, (off_t)(afterheader), SEEK_SET ) == (off_t)(-1) )
		{
			printf("\033[31m\033[1mCan not seek back to the beginning of file ? Abort.\033[0m\n");
			myexit(1);
					}
					
	if ( lseek( dcd, (off_t)(bytes_per_set * (off_t)(REFERENCE-1)), SEEK_CUR ) == (off_t)(-1) )
			{
				printf("\033[31m\033[1mRequested reference frame not present ? Abort.\033[0m\n");
				myexit(1);
						}

						/* Mark current position */
	start_ref = lseek( dcd, (off_t)(0), SEEK_CUR );


/* Quick and dirty : open output dcd, copy everything as is up to the start of data from the input file, */
/* and then start modifying the CA coordinates only and writing out the whole block */

#ifdef WINDOWS
	outdcd = open( "carma.fitted.dcd", O_WRONLY | O_CREAT | O_TRUNC | O_BINARY | O_RANDOM, S_IRUSR | S_IWUSR );
#else
	outdcd = open( "carma.fitted.dcd", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP );
#endif

	if ( outdcd == -1 )
		{
			printf("\033[31m\033[1mCan not open DCD file for output. Abort.\033[0m\n");
			myexit( 1 );
					}

	outdcdhead = malloc( (size_t)(afterheader) );


	if ( lseek( dcd, (off_t)(0), SEEK_SET ) == (off_t)(-1) )
		{
			printf("\033[31m\033[1mCan not seek back to the beginning of file ? Abort.\033[0m\n");
			myexit(1);
					}
	if ( (off_t)(read( dcd, outdcdhead, (size_t)(afterheader) )) != afterheader )
		{
			printf("\033[31m\033[1mPremature EOF for DCD file ? Abort.\033[0m\n");
			myexit(1);
					}


	if ( WRITE_CAS == YES )
		*((unsigned int *)(&outdcdhead[afterheader-8])) = (unsigned int)(nofCAs);

	if ( (off_t)(write( outdcd, outdcdhead, (size_t)(afterheader) )) != afterheader )
		{
			printf("\033[31m\033[1mFailed to write header block to DCD file ? Abort.\033[0m\n");
			myexit(1);
					}
	if ( lseek( dcd, (off_t)(start_ref), SEEK_SET ) == (off_t)(-1) )
		{
			printf("\033[31m\033[1mCan not seek back to the reference frame ? Abort.\033[0m\n");
			myexit(1);
					}



	REF_xyz = vector( 1, 3*nofCAs );
	FIT_xyz = vector( 1, 3*nofCAs );
	for ( i=1 ; i <= 3*nofCAs ; i++ )
		{
			REF_xyz[i] = 0.0;
			FIT_xyz[i] = 0.0;
						}
								

	/* Read reference frame and go back to the beginning */
	if ( (unsigned int)(read( dcd, (void *)(&dcd_frame[1]), (size_t)(bytes_per_set) )) != bytes_per_set )
		{
			if ( VERBOSE )
				printf("\033[31m\033[1m\nCan not read reference frame ? Abort.\033[0m\n");
			myexit(1);
					}

	build_CAs( (int)(nofatoms) + 2);

	for ( i=0 ; i < nofCAs ; i++ )
		{
			REF_xyz[i*3+1] = CAs[i][0];
			REF_xyz[i*3+2] = CAs[i][1];
			REF_xyz[i*3+3] = CAs[i][2];
						}

	if ( lseek( dcd, (off_t)(start), SEEK_SET ) == (off_t)(-1) )
		{
			printf("\033[31m\033[1mCan not seek back to the beginning of data ? Abort.\033[0m\n");
			myexit(1);
					}

	rms_evolution = fopen("carma.fit-rms.dat", "w");
	if ( rms_evolution == NULL )
		{	
			printf("\033[31m\033[1mCan not open output file. Abort.\033[0m\n");
			myexit(1);
					}
		

	entered = 0;
	frame = firstframe;
	if ( REF_STEP > 0 )
		STEP = REF_STEP;

	if ( VERBOSE )
	printf("Now processing frame %8d", frame);
	while( frame <= LAST )
		{
		if ( (unsigned int)(read( dcd, (void *)(&dcd_frame[1]), (size_t)(bytes_per_set) )) != bytes_per_set )
			{
				if ( VERBOSE )
				printf("%8d", (frame-1) );
				if ( frame == FIRST )
					{
						if ( VERBOSE )
						printf("\033[31m\033[1m\nRequested frame not present ? Abort.\033[0m\n");
						myexit(1);
								}
				if ( VERBOSE )
				printf("\nEnd of DCD reached.\n");
				break;
									}
				

		sprintf( framestring, "%d", frame );
		if ( (frame-firstframe) % STEP == 0 )
		{		
		build_CAs( (int)(nofatoms) + 2);

		for ( i=0 ; i < nofCAs ; i++ )
			{
				FIT_xyz[i*3+1] = CAs[i][0];
				FIT_xyz[i*3+2] = CAs[i][1];
				FIT_xyz[i*3+3] = CAs[i][2];
								}


		if ( NOFIT == YES )
		{
			float	sum, ddx, ddy, ddz;

			sum = 0.0;
			for ( i=0 ; i < nofCAs ; i++ )
				{
					ddx = FIT_xyz[i*3+1] - REF_xyz[i*3+1];
					ddy = FIT_xyz[i*3+2] - REF_xyz[i*3+2];
					ddz = FIT_xyz[i*3+3] - REF_xyz[i*3+3];
					sum += ddx*ddx + ddy*ddy + ddz*ddz;
				}
				current_rms = sqrt( sum / (float)(nofCAs) );

		fprintf(rms_evolution, " % 7d % 9.4f\n", frame, current_rms );
		
		}
		else
		{

		current_rms = bestfit( rot_matrix, trans_matrix, &FIT_xyz[1], &REF_xyz[1], nofCAs );


		fprintf(rms_evolution, " % 7d % 9.4f %+12.8f %+12.8f %+12.8f %+12.8f %+12.8f %+12.8f %+12.8f %+12.8f %+12.8f %+12.8f %+12.8f %+12.8f \n", 
			frame, current_rms, rot_matrix[0][0], rot_matrix[0][1], rot_matrix[0][2]
			, rot_matrix[1][0], rot_matrix[1][1], rot_matrix[1][2]
			, rot_matrix[2][0], rot_matrix[2][1], rot_matrix[2][2]
			, trans_matrix[0], trans_matrix[1], trans_matrix[2] );


		if ( REF_STEP > 0 )
			{
				for ( i=0 ; i < nofCAs ; i++ )
					{
						REF_xyz[i*3+1] = CAs[i][0];
						REF_xyz[i*3+2] = CAs[i][1];
						REF_xyz[i*3+3] = CAs[i][2];
										}
			}


		for ( i=0 ; i < nofCAs ; i++ )
			{
			CAs[i][0] =   	rot_matrix[0][0]*FIT_xyz[i*3+1] + rot_matrix[0][1]*FIT_xyz[i*3+2] 
				      + rot_matrix[0][2]*FIT_xyz[i*3+3] + trans_matrix[0];
			CAs[i][1] =   	rot_matrix[1][0]*FIT_xyz[i*3+1] + rot_matrix[1][1]*FIT_xyz[i*3+2] 
				      + rot_matrix[1][2]*FIT_xyz[i*3+3] + trans_matrix[1];
			CAs[i][2] =   	rot_matrix[2][0]*FIT_xyz[i*3+1] + rot_matrix[2][1]*FIT_xyz[i*3+2] 
				      + rot_matrix[2][2]*FIT_xyz[i*3+3] + trans_matrix[2];
			}



		if ( FAST_MAP )
		{
		for ( i=0 ; i < fmap_nofatoms ; i++ )
			{
				if ( fmapindeces[i] >= nofCAs )
				{
					printf("\033[31m\033[1mToo large index in \"fmap.index\". Abort.\033[0m\n" );
					myexit(1);
							}

				gx = (int)(gridx * (CAs[fmapindeces[i]][0] - Xmin) / (Xmax-Xmin) + 0.50) + 1;
				gy = (int)(gridy * (CAs[fmapindeces[i]][1] - Ymin) / (Ymax-Ymin) + 0.50) + 1;
				gz = (int)(gridz * (CAs[fmapindeces[i]][2] - Zmin) / (Zmax-Zmin) + 0.50) + 1;

				if ( gx >= 1 && gx <= gridx && gy >= 1 && gy <= gridy && gz >= 1 && gz <= gridz )
					map[gx][gy][gz] += 1.0;
						}
			
		if ( WRITE_CAS == YES )
			write_CAs2( (int)(nofCAs) + 2);
		else
			write_CAs( (int)(nofatoms) + 2);

		}
		else
		{
		if ( WRITE_CAS == YES )
			{
			write_CAs2( (int)(nofCAs) + 2);
		
			if ( (unsigned int)(write( outdcd, (void *)(&wdcd_frame[1]), (size_t)(wbytes_per_set) )) != wbytes_per_set )
				{
					printf("\033[31m\033[1mFailed to write frame %d to DCD file.\033[0m\n", frame );
					myexit(1);
							}
								}
		else
			{	
			write_CAs( (int)(nofatoms) + 2);
		
			if ( (unsigned int)(write( outdcd, (void *)(&dcd_frame[1]), (size_t)(bytes_per_set) )) != bytes_per_set )
				{
					printf("\033[31m\033[1mFailed to write frame %d to DCD file.\033[0m\n", frame );
					myexit(1);
							}
								}
		
		}
		}
		
		entered++;

		if ( STEP > 1 )
			{
				if ( lseek( dcd, (off_t)(bytes_per_set * (off_t)(STEP-1)), SEEK_CUR ) == (off_t)(-1) )
				{
					printf("\033[31m\033[1mRequested frame not present ? Abort.\033[0m\n");
					myexit(1);
							}
				frame += (STEP-1);
			}
		}
		frame++;
		if ( VERBOSE )
		printf("%8d", frame );


						}

	if ( frame == LAST+1 && VERBOSE )
		printf("%8d\n", (frame-1) );

	
	close( outdcd );
	fclose(rms_evolution);


	if ( FAST_MAP )
	{
	max = 0.0;
	mapaver = 0.0;
	mapsigma = 0.0;
	for ( i=0 ; i < gridx*gridy*gridz ; i++ )
		{
			if ( pmap[i] > max )
				max =  pmap[i];
			mapaver += pmap[i];
						}

	mapaver /= (float)(gridx*gridy*gridz);
	for ( i=0 ; i < gridx*gridy*gridz ; i++ )
		mapsigma += (pmap[i]-mapaver)*(pmap[i]-mapaver);

	mapsigma = sqrt( mapsigma / (float)(gridx*gridy*gridz));


	if ( VERBOSE )
		{
			printf("Maximum count recorded is %f\n", max );
			printf("Map average and sigma are %f and %f\n", mapaver, mapsigma );
		}
		

	sprintf( frameno, ".map");
	strcpy( filename, strrchr( argv[HAVE_DCD], '/') != NULL ? strrchr( argv[HAVE_DCD], '/') + 1 : argv[HAVE_DCD] );
	strcat( filename, frameno );

	cns = fopen( filename, "w");
        if ( cns == NULL )
                {
                printf("\033[31m\033[1mCan not open map file for writing. Abort.\n");
                myexit(1);
                }

	fprintf(cns, "\n");
	fprintf(cns, "       2\n");
	fprintf(cns, " REMARKS FILENAME=\"%s\"\n", filename);
	fprintf(cns, " REMARKS Created by Carma\n");
	fprintf(cns, "%7d %7d %7d %7d %7d %7d %7d %7d %7d\n", gridx, (int)(Xmin*gridx/(Xmax-Xmin)), (int)(Xmax*gridx/(Xmax-Xmin)-1),
							gridy, (int)(Ymin*gridy/(Ymax-Ymin)), (int)(Ymax*gridy/(Ymax-Ymin)-1),
							gridz, (int)(Zmin*gridz/(Zmax-Zmin)), (int)(Zmax*gridz/(Zmax-Zmin)-1) );
	fprintf(cns, "%7.5E %7.5E %7.5E %7.5E %7.5E %7.5E\n", Xmax-Xmin, Ymax-Ymin, Zmax-Zmin, 90.0, 90.0, 90.0 );
	fprintf(cns, "ZYX\n");
	for (gz=1 ; gz <= gridz ; gz ++)
	{
	i = 0;
	fprintf(cns, "%8d\n", gz-1 );
	for (gy=1 ; gy <= gridy ; gy ++)
	for (gx=1 ; gx <= gridx ; gx ++)
		{
			fprintf(cns, "%+8.5E", map[gx][gy][gz] );
			i++;
			if ( i == 6 )
				{
					i = 0;
					fprintf(cns, "\n");
				}
		}


	if ( i != 0 )
		fprintf(cns, "\n");

	}
	
	fprintf(cns, "   -9999\n");

	fprintf(cns, "%12.4E%12.4E\n", mapaver, mapsigma );

	fclose(cns);
	}

#ifndef WINDOWS	
	if ( VERBOSE )
		{
		end_timer = time(NULL);
		printf("\033[32m\033[1mAll done in %1.1f minutes.\033[0m\n", (float)(end_timer-start_timer)/60.0 );
		}
#endif
	
	myexit( 0 );
	


}






/*****************************************************************************************************************************/
/**	'CROSSDCD' Keyword 												    **/
/*****************************************************************************************************************************/



	if ( CROSSDCD == YES )
	{	
	float		*REF_xyz;
	float		*FIT_xyz;
	float		current_rms;
	rotate_t 	rot_matrix;
	xlate_t		trans_matrix;
	FILE		*rms_evolution;
	float		sssize;


	if ( LAST > headerframes )
		LAST = headerframes;
	
	afterheader = lseek( dcd, (off_t)(0), SEEK_CUR );

	if ( VERBOSE )
		printf("Calculate RMSD matrix for trajectory.\n");


	if ( (sssize = ((float)(LAST) - FIRST +1.0)/(float)(STEP)) > 10000.0 )
		{
		printf("\033[31m\033[1mIf the DCD header is correct, this will create a %4.2f MBytes matrix file.\033[0m\n", 
				sssize*sssize*5 / (1024*1024) );
				
#ifndef WINDOWS
		sleep(2);
#endif	
		if ( VERBOSE && sssize > 20000.0 )
			printf("\033[33mOK. This will be a depressingly long calculation ...\033[0m\n");
		}


	if ( FIRST > 1 )
		if ( lseek( dcd, (off_t)(bytes_per_set * (off_t)(FIRST-1)), SEEK_CUR ) == (off_t)(-1) )
			{
				printf("\033[31m\033[1mRequested frame not present ? Abort.\033[0m\n");
				myexit(1);
						}


						/* Mark current position */
	start = lseek( dcd, (off_t)(0), SEEK_CUR );


	rms_evolution = fopen("carma.RMSD.matrix", "w");
	if ( rms_evolution == NULL )
		{	
			printf("\033[31m\033[1mCan not open output file. Abort.\033[0m\n");
			myexit(1);
					}
		

	REF_xyz = vector( 1, 3*nofCAs );
	FIT_xyz = vector( 1, 3*nofCAs );


	if ( VERBOSE )
	printf("Now processing frame %8d", FIRST );



	/************************************/ 				
	/* Outer loop over reference frames */
	/************************************/									
	for ( REFERENCE = FIRST ; REFERENCE <= LAST ; REFERENCE += STEP )
	{


	if ( lseek( dcd, (off_t)(afterheader), SEEK_SET ) == (off_t)(-1) )
		{
			printf("\033[31m\033[1mCan not seek back to the beginning of file ? Abort.\033[0m\n");
			myexit(1);
					}

					
	if ( lseek( dcd, (off_t)(bytes_per_set * (off_t)(REFERENCE-1)), SEEK_CUR ) == (off_t)(-1) )
			{
				printf("\033[31m\033[1mRequested reference frame not present ? Abort.\033[0m\n");
				myexit(1);
						}

						/* Mark current position */
	start_ref = lseek( dcd, (off_t)(0), SEEK_CUR );




	for ( i=1 ; i <= 3*nofCAs ; i++ )
		{
			REF_xyz[i] = 0.0;
			FIT_xyz[i] = 0.0;
						}
								

	/* Read reference frame and go back to the beginning */
	if ( (unsigned int)(read( dcd, (void *)(&dcd_frame[1]), (size_t)(bytes_per_set) )) != bytes_per_set )
		{
			if ( VERBOSE )
				printf("\033[31m\033[1m\nCan not read reference frame ? Abort.\033[0m\n");
			myexit(1);
					}

	build_CAs( (int)(nofatoms) + 2);

	for ( i=0 ; i < nofCAs ; i++ )
		{
			REF_xyz[i*3+1] = CAs[i][0];
			REF_xyz[i*3+2] = CAs[i][1];
			REF_xyz[i*3+3] = CAs[i][2];
						}

	if ( lseek( dcd, (off_t)(start), SEEK_SET ) == (off_t)(-1) )
		{
			printf("\033[31m\033[1mCan not seek back to the beginning of data ? Abort.\033[0m\n");
			myexit(1);
					}






	entered = 0;
	frame = firstframe;


	if ( VERBOSE )
		printf("%8d", REFERENCE );

	while( frame <= LAST )
		{
		if ( (unsigned int)(read( dcd, (void *)(&dcd_frame[1]), (size_t)(bytes_per_set) )) != bytes_per_set )
			{
				if ( frame == FIRST )
					{
						if ( VERBOSE )
						printf("\033[31m\033[1m\nRequested frame not present ? Abort.\033[0m\n");
						myexit(1);
								}
				break;
									}
				

		if ( (frame-firstframe) % STEP == 0 )
		{		
		build_CAs( (int)(nofatoms) + 2);

		for ( i=0 ; i < nofCAs ; i++ )
			{
				FIT_xyz[i*3+1] = CAs[i][0];
				FIT_xyz[i*3+2] = CAs[i][1];
				FIT_xyz[i*3+3] = CAs[i][2];
								}



		current_rms = bestfit( rot_matrix, trans_matrix, &FIT_xyz[1], &REF_xyz[1], nofCAs );


		fprintf(rms_evolution, " %4.2f", fabs(current_rms) );


		entered++;

		if ( STEP > 1 )
			{
				if ( lseek( dcd, (off_t)(bytes_per_set * (off_t)(STEP-1)), SEEK_CUR ) == (off_t)(-1) )
				{
					printf("\033[31m\033[1mRequested frame not present ? Abort.\033[0m\n");
					myexit(1);
							}
				frame += (STEP-1);
			}
		}
		
		frame++;


						}

	fprintf(rms_evolution, "\n");
	
	}
	
	fclose(rms_evolution);


	if ( VERBOSE && REFERENCE == LAST + 1)
		printf("%8d\n", REFERENCE-1 );
	else if ( VERBOSE )
		printf("%8d\n", REFERENCE );
	
#ifndef WINDOWS	
	if ( VERBOSE )
		{
		end_timer = time(NULL);
		printf("\033[32m\033[1mAll done in %1.1f minutes.\033[0m\n", (float)(end_timer-start_timer)/60.0 );
		}
#endif
	
	myexit( 0 );
	


}









/*****************************************************************************************************************************/
/**	dPCA														    **/
/*****************************************************************************************************************************/



	if ( DPCA == YES )
	{	
	float	*CA_t;
	float	*averCA_t;
	double 	tors;
	int	at1, at2, at3, at4;
	int	inter;

/*
	for ( i=0 ; i < nofCAs ; i++ )
		printf("%s\n", backbone[i] );
*/


	if ( CHI1 == NO )	
		nof_torsions = build_torsions();
	else
		nof_torsions = build_torsions_with_chi();
	





/*****************************************************************************************************************************/
/**   Calculate average metric for all torsions						                                    **/
/*****************************************************************************************************************************/

	averCA_t = vector( 1, 2*nof_torsions );
	CA_t     = vector( 1, 2*nof_torsions );
	for ( i=1 ; i <= 2*nof_torsions ; i++ )
		{
			CA_t[i] = 0.0;
			averCA_t[i] = 0.0;
						}
								

	D2 = matrix( 1, 2*nof_torsions, 1, 2*nof_torsions );
	pD2 = &D2[1][1];
	for ( i=0 ; i < 4*nof_torsions*nof_torsions ; i++ )
			pD2[i] = 0.0;

	
	
	afterheader = lseek( dcd, (off_t)(0), SEEK_CUR );

	if ( VERBOSE )
	printf("First pass to determine average metric coordinates for %d torsions\n", nof_torsions);

	if ( FIRST > 1 )
		if ( lseek( dcd, (off_t)(bytes_per_set * (off_t)(FIRST-1)), SEEK_CUR ) == (off_t)(-1) )
			{
				printf("\033[31m\033[1mRequested frame not present ? Abort.\033[0m\n");
				myexit(1);
						}
						

						/* Mark current position */
	start = lseek( dcd, (off_t)(0), SEEK_CUR );

	entered = 0;
	frame = firstframe;
	if ( VERBOSE )
	printf("Now processing frame %8d", frame);
	while( frame <= LAST )
		{
		if ( (unsigned int)(read( dcd, (void *)(&dcd_frame[1]), (size_t)(bytes_per_set) )) != bytes_per_set )
			{
				if ( VERBOSE )
				printf("%8d", (frame-1) );
				if ( frame == FIRST )
					{
						printf("\033[31m\033[1m\nRequested frame not present ? Abort.\033[0m\n");
						myexit(1);
								}
				if ( VERBOSE )
				printf("\nEnd of DCD reached.\n");
				break;
									}
		sprintf( framestring, "%d", frame );

		if ( (frame-firstframe) % STEP == 0 )
		{		
		entered++;		
		build_CAs( (int)(nofatoms) + 2);

		for ( i=0 ; i < nof_torsions ; i++ )
			{
				at1 = tetraplets[i][0];
				at2 = tetraplets[i][1];
				at3 = tetraplets[i][2];
				at4 = tetraplets[i][3];

				tors = M_PI * torsion(
					CAs[ at1 ][0], CAs[ at1 ][1], CAs[ at1 ][2],
					CAs[ at2 ][0], CAs[ at2 ][1], CAs[ at2 ][2],
					CAs[ at3 ][0], CAs[ at3 ][1], CAs[ at3 ][2],
					CAs[ at4 ][0], CAs[ at4 ][1], CAs[ at4 ][2] ) / 180.0;

/*
				printf("\n Torsion %2d, atoms %3d %3d %3d %3d, value %7.3f  (%7.3f)\n",
					i, at1, at2, at3, at4, tors,
					torsion(
					CAs[ at1 ][0], CAs[ at1 ][1], CAs[ at1 ][2],
					CAs[ at2 ][0], CAs[ at2 ][1], CAs[ at2 ][2],
					CAs[ at3 ][0], CAs[ at3 ][1], CAs[ at3 ][2],
					CAs[ at4 ][0], CAs[ at4 ][1], CAs[ at4 ][2] ) );
*/		

				averCA_t[i*2+1] += cos( tors );
				averCA_t[i*2+2] += sin( tors );
						}

		if ( STEP > 1 )
			{
				if ( lseek( dcd, (off_t)(bytes_per_set * (off_t)(STEP-1)), SEEK_CUR ) == (off_t)(-1) )
				{
					printf("\033[31m\033[1mRequested frame not present ? Abort.\033[0m\n");
					myexit(1);
							}
				frame += (STEP-1);
			}
		}
		frame++;
		if ( VERBOSE )
		printf("%8d", frame );


						}

	if ( frame == LAST+1 )
		{
		if ( VERBOSE )
		printf("%8d\n", (frame-1) );
		}
	
	totentered = entered;
	
	if ( VERBOSE )						
	printf("%d frames entered the calculation.\n", entered );

	for ( i=1 ; i <= 2*nof_torsions ; i++ )
		averCA_t[i] /= (float)(entered);




/*****************************************************************************************************************************/
/**   Second pass for displacements	                                                                                    **/
/*****************************************************************************************************************************/



	if ( lseek( dcd, (off_t)(start), SEEK_SET ) == (off_t)(-1) )
		{
			printf("\033[31m\033[1mCan not seek back to the beginning of data ? Abort.\033[0m\n");
			myexit(1);
					}



	if ( VERBOSE )
	printf("Second pass to calculate dihedral angle variances ...\n");

	entered = 0;
	frame = firstframe;
	if ( VERBOSE )
	printf("Now processing frame %8d", frame);
	while( frame <= LAST )
		{
		if ( (unsigned int)(read( dcd, (void *)(&dcd_frame[1]), (size_t)(bytes_per_set) )) != bytes_per_set )
			{
				if ( VERBOSE )
				printf("%8d", (frame-1) );
				if ( frame == FIRST )
					{
						if ( VERBOSE )
						printf("\033[31m\033[1m\nRequested frame not present ? Abort.\033[0m\n");
						myexit(1);
								}
				if ( VERBOSE )
				printf("\nEnd of DCD reached. Write variance-covariance map.\n");
				break;
									}
				
		sprintf( framestring, "%d", frame );

		if ( (frame-firstframe) % STEP == 0 )
		{		
		entered++;		
		build_CAs( (int)(nofatoms) + 2);



		for ( i=0 ; i < nof_torsions ; i++ )
			{
				at1 = tetraplets[i][0];
				at2 = tetraplets[i][1];
				at3 = tetraplets[i][2];
				at4 = tetraplets[i][3];

				tors = M_PI * torsion(
					CAs[ at1 ][0], CAs[ at1 ][1], CAs[ at1 ][2],
					CAs[ at2 ][0], CAs[ at2 ][1], CAs[ at2 ][2],
					CAs[ at3 ][0], CAs[ at3 ][1], CAs[ at3 ][2],
					CAs[ at4 ][0], CAs[ at4 ][1], CAs[ at4 ][2] ) / 180.0;

				CA_t[i*2+1] = cos( tors );
				CA_t[i*2+2] = sin( tors );
						}
			


									/* averCA_t[] has the averages */
									/* CA_t[] has this frame's coordinates */
									/* Use them to populate D2[][] which will */
									/* become the covariance matrix */


		for ( i=1 ; i <= 2*nof_torsions ; i++)
		for ( k=i ; k <= 2*nof_torsions ; k++)
		D2[i][k] += CA_t[i]*CA_t[k] +averCA_t[i]*averCA_t[k] -CA_t[i]*averCA_t[k] -averCA_t[i]*CA_t[k];


		if ( STEP > 1 )
			{
				if ( lseek( dcd, (off_t)(bytes_per_set * (off_t)(STEP-1)), SEEK_CUR ) == (off_t)(-1) )
				{
					printf("\033[31m\033[1mRequested frame not present ? Abort.\033[0m\n");
					myexit(1);
							}
				frame += (STEP-1);
			}
		}
		frame++;
		if ( VERBOSE )
		printf("%8d", frame );


						}

	if ( frame == LAST+1 && VERBOSE )
		printf("%8d\n", (frame-1) );

	for ( i=1 ; i <= 2*nof_torsions ; i++)
	for ( k=i ; k <= 2*nof_torsions ; k++)
		{
			D2[k][i] = D2[i][k];							
				}

	
	
	totentered = entered;
		
	
	if ( VERBOSE )
	printf("%d frames entered the calculation.\n", entered );


	max = -1000000000000.0 ;
	min =  1000000000000.0 ; 

	for ( i=0 ; i < 4*nof_torsions*nof_torsions ; i++ )
		{
			pD2[i] = pD2[i] / (float)(entered);
			if ( pD2[i] > max )
				max =  pD2[i];
			if ( pD2[i] < min )
				min =  pD2[i];

						}
	
	
	sprintf( frameno, ".dPCA.varcov");
	strcpy( filename, strrchr( argv[HAVE_DCD], '/') != NULL ? strrchr( argv[HAVE_DCD], '/') + 1 : argv[HAVE_DCD] );
	strcat( filename, frameno );
	


	if ( VERBOSE )
		{
			printf("Maximum of variance-covariance matrix is %f\n", max );
			printf("Minimum of variance-covariance matrix is %f\n", min );
					}			
					
	REVERSE = !REVERSE ;
	if ( HAVE_MIN == NO )
		gmin = min;
	if ( HAVE_MAX == NO )
		gmax = max;
		


	inter = nofCAs;
	nofCAs = nof_torsions * 2;
		
	wps( D2, filename );


#if defined (LAPACK) || defined (NR)

	eigendim = nofCAs;
				
	eigen( D2 );

	nofCAs = inter;



/*****************************************************************************************************************************/
/**	Third pass to calculate projection of trajectory's fluctuations onto eigenvector				    **/
/*****************************************************************************************************************************/

	if ( EIGENFIRST > 0 )
	{
	FILE 	*proj;
	float	sum = 0.0;



								/* Allocate a matrix for the DG plots (calcs later on) */
	if ( DG_PLOTS > 0 )
	{
	DG = matrix( 1, totentered, 1, DG_PLOTS );
	}



	proj = fopen( "carma.dPCA.fluctuations.dat", "w");
	if ( proj == NULL )
		{	
			printf("\033[31m\033[1mCan not open output file. Abort.\033[0m\n");
			myexit(1);
					}
	
	if ( lseek( dcd, (off_t)(start), SEEK_SET ) == (off_t)(-1) )
		{
			printf("\033[31m\033[1mCan not seek back to the beginning of data ? Abort.\033[0m\n");
			myexit(1);
					}



	if ( VERBOSE )
		{
		printf("Third pass to determine dihedral angle fluctuations along eigenvectors.\n");
		printf("Chosen eigenvectors are : \n");
		i = 0;
		for ( k=EIGENFIRST ; k <= EIGENLAST ; k += EIGENSTEP )
			{
				printf("%d ", k );
				i++;
				if ( i > 9 )
					{
					i = 0;
					printf("\n");
					}
					}	
		printf("\n");
		}


	entered = 0;
	frame = firstframe;
	if ( VERBOSE )
	printf("Now processing frame %8d", frame);
	while( frame <= LAST )
		{
		if ( (unsigned int)(read( dcd, (void *)(&dcd_frame[1]), (size_t)(bytes_per_set) )) != bytes_per_set )
			{
				if ( VERBOSE )
				printf("%8d", (frame-1) );
				if ( frame == FIRST )
					{
						if ( VERBOSE )
						printf("\033[31m\033[1m\nRequested frame not present ? Abort.\033[0m\n");
						myexit(1);
								}
				if ( VERBOSE )
				printf("\nEnd of DCD reached.\n");
				break;
									}
				
		sprintf( framestring, "%d", frame );

		if ( (frame-firstframe) % STEP == 0 )
		{		
		entered++;		
		if ( entered > totentered )
			{
				printf("\033[31m\033[1m\nThe DCD file is still growing ? Use the \"-last\" flag. Aborting.\033[0m\n");
				myexit( 1 );
			}
		build_CAs( (int)(nofatoms) + 2);

		for ( i=0 ; i < nof_torsions ; i++ )
			{
				at1 = tetraplets[i][0];
				at2 = tetraplets[i][1];
				at3 = tetraplets[i][2];
				at4 = tetraplets[i][3];

				tors = M_PI * torsion(
					CAs[ at1 ][0], CAs[ at1 ][1], CAs[ at1 ][2],
					CAs[ at2 ][0], CAs[ at2 ][1], CAs[ at2 ][2],
					CAs[ at3 ][0], CAs[ at3 ][1], CAs[ at3 ][2],
					CAs[ at4 ][0], CAs[ at4 ][1], CAs[ at4 ][2] ) / 180.0;

				CA_t[i*2+1] = cos( tors ) - averCA_t[i*2+1];
				CA_t[i*2+2] = sin( tors ) - averCA_t[i*2+2];
						}


		fprintf(proj, "%7d ", frame );
		for ( k=EIGENFIRST ; k <= EIGENLAST ; k += EIGENSTEP )
		{
		sum = 0.0;
		for ( i=1 ; i <= eigendim ; i++ )
			sum += CA_t[i] * eigenvectors[i][k];
		
		fprintf(proj, "%12.7f ", sum );

		if ( DG_PLOTS > 0 && (k-EIGENFIRST+1) <= DG_PLOTS )
			DG[entered][k-EIGENFIRST+1] = sum;

		}
		fprintf(proj, "\n");
		
		if ( STEP > 1 )
			{
				if ( lseek( dcd, (off_t)(bytes_per_set * (off_t)(STEP-1)), SEEK_CUR ) == (off_t)(-1) )
				{
					printf("\033[31m\033[1mRequested frame not present ? Abort.\033[0m\n");
					myexit(1);
							}
				frame += (STEP-1);
			}

		}
		frame++;
		if ( VERBOSE )
		printf("%8d", frame );


						}

	if ( frame == LAST+1 && VERBOSE )
		printf("%8d\n", (frame-1) );



	/***********************************************************************/
	/* DG[][] contains the fluctuations for each frame and every           */
	/* eigenvector. We bin the data, convert to probabilities (normalise), */
	/* take the logarithms, multiply with kB & temp, and export            */
	/***********************************************************************/

	if ( DG_PLOTS > 0 )
	{
	int 	tframes;
	int	v1, v2, frame;
	int	bins, bins2;	
	int	m;
	float	v1max, v1min, val, limit;
	float	**PLOT;
	float	val1, val2, val3;
	int	pos1, pos2, pos3;
	float	wmax, wsum;

	bins2 = 0;
	tframes = totentered;

/*
	for ( v1 = 1 ; v1 <= tframes ; v1++ )
	for ( v2 = 1 ; v2 <= DG_PLOTS ; v2++ )
		printf(" %6d %6d %12.7f\n", v1, v2, DG[v1][v2] );
*/

	bins = (int)( sqrt( (double)( tframes) ) / 2);		/* number of bins for plot */
	if ( bins < 4 )
		{
			printf("\033[31m\033[1m\nToo few (%d) bins for DeltaG plots. Abort.\033[0m\n", bins);
			myexit(1);
		}
	if ( bins < 30 && VERBOSE )
		{
			printf("\033[31m\033[1m\nWarning: very few (%d) bins for DeltaG plots.\033[0m\n", bins);
		}

								/* Allocate 2D array for plot data */
	PLOT = matrix( 1, bins, 1, bins );



	/* Determine limits of plots */

	v1max = DG[1][1];
	v1min = DG[1][1];
	for ( v1 = 1 ; v1 < tframes ; v1++ )
	for ( v2 = 1 ; v2 <= DG_PLOTS ; v2++ )
		{
			val = DG[v1][v2];
			if ( val > v1max )
				v1max = val;
			if ( val < v1min )
				v1min = val;
		}
		
	if ( DGLEN < 0.0 )
		limit = 1.20 * max2( fabs( v1max), fabs( v1min));
	else
		limit = DGLEN / 2.0;
		
	if ( VERBOSE )
		printf("DeltaG plots will extend from %+5.2f to %+5.2f.\n", -limit, limit);



						/* Prepare 3D matrix for cluster analysis */
	if ( DG_PLOTS >= 3 ) 
		{
		bins2 = 2 * (int)((int)( pow( (double)( tframes), 1.0/3.0 ) +0.50) / 2 +0.50);

		CLUSTER = f3tensor( 1, bins2, 1, bins2, 1, bins2 );
		for ( i = 1 ; i <= bins2 ; i++ )
		for ( k = 1 ; k <= bins2 ; k++ )
		for ( m = 1 ; m <= bins2 ; m++ )
			CLUSTER[i][k][m] = 0.0;
		for ( frame = 1 ; frame <= tframes ; frame++ )
			{
				val1 = DG[frame][1];
				val2 = DG[frame][2];
				val3 = DG[frame][3];
		
				pos1 = (int)( bins2 * (val1 + limit) / (2.0*limit) + 0.50 )+1;
				pos2 = (int)( bins2 * (val2 + limit) / (2.0*limit) + 0.50 )+1;
				pos3 = (int)( bins2 * (val3 + limit) / (2.0*limit) + 0.50 )+1;
		
				CLUSTER[pos1][pos2][pos3] += 1.0;
			}
		}


	REVERSE = !REVERSE ;

	/* The plots in terms of eigenvectors */

	for ( v1 = 1    ; v1 <  DG_PLOTS ; v1++ )
	for ( v2 = v1+1 ; v2 <= DG_PLOTS ; v2++ )
	{
	wsum = 0.0;
	wmax = 0.0;
	for ( i = 1 ; i <= bins ; i++ )
	for ( k = 1 ; k <= bins ; k++ )
		PLOT[i][k] = 0.90;

	for ( frame = 1 ; frame <= tframes ; frame++ )
	{
		val1 = DG[frame][v1];
		val2 = DG[frame][v2];
		
		pos1 = (int)( bins * (val1 + limit) / (2.0*limit) + 0.50 )+1;
		pos2 = (int)( bins * (val2 + limit) / (2.0*limit) + 0.50 )+1;

		PLOT[pos1][pos2] += 1.0;

		if ( PLOT[pos1][pos2] > wmax )
			wmax = PLOT[pos1][pos2];

		wsum += 1.0;
	}

	gmax = -1000000000000.0 ;
	gmin =  1000000000000.0 ; 
	for ( i = 1 ; i <= bins ; i++ )
	for ( k = 1 ; k <= bins ; k++ )
		{
			val = - DGCONST * DGTEMP * log( PLOT[i][k] / (double)(wmax) ) ;
			PLOT[i][k] = val;
			if ( val > gmax )
				gmax = val;
			if ( val < gmin )
				gmin = val;
		}

	if ( VERBOSE )
		{
			printf("Maximum of the %02d - %02d DeltaG plot is %f kcal/mol\n", v1, v2, gmax );
					}			

	sprintf( pscomment, "Dihedral PCA DeltaG plot. Vectors %02d - %02d, ranging from %f to %f. DeltaG values: %f to zero.",
			v1, v2, -limit, limit, gmax );

	nofCAs = bins;
	sprintf( filename, "carma.dPCA.DG_%02d_%02d", v1, v2 );
	wps( PLOT, filename );


	}

	free_matrix(PLOT, 1, bins, 1, bins );

	if ( DG_PLOTS >= 3 ) 
		cluster( bins2, tframes, limit );

	}

	/*****************     END DG_PLOT          ****************************/


	
#ifndef WINDOWS
	if ( VERBOSE )
		{
		end_timer = time(NULL);
		printf("\033[32m\033[1mAll done in %1.1f minutes.\033[0m\n", (float)(end_timer-start_timer)/60.0 );
		}
#endif

	
	fclose( proj );
	myexit( 0 );
	

	
	}

#endif











	myexit( 0 );






}










/*****************************************************************************************************************************/
/**	This is the accessible surface area calculation									    **/
/*****************************************************************************************************************************/



	if ( ASA == YES )
	{	
	FILE 	*proj;
	unsigned short int	***ed;
	unsigned short int	profile[17][17][17];
	float	maxx, maxy, maxz;
	float	minx, miny, minz;
	float	dim_x, dim_y, dim_z;
	int	grid_x, grid_y, grid_z;
	int	xint, yint, zint;
	int	xxx, yyy, zzz;
	int	o, p, q;
	float	dx, dy, dz, dist;
	float	aver, sum;


	proj = fopen( "carma.surface.dat", "w");
	if ( proj == NULL )
		{	
			printf("\033[31m\033[1mCan not open output file. Abort.\033[0m\n");
			myexit(1);
					}

	
							/* Our one & only atomic density profile of 3.2A radius with */
							/* a 0.4A grid step */
        for ( dx = -3.20, xxx=0 ; dx <= 3.21 ; dx += 0.40, xxx++ )
        for ( dy = -3.20, yyy=0 ; dy <= 3.21 ; dy += 0.40, yyy++ )
        for ( dz = -3.20, zzz=0 ; dz <= 3.21 ; dz += 0.40, zzz++ )
                {
                        dist = sqrt( dx*dx + dy*dy + dz*dz );
                        if ( dist <= 3.21 )
				profile[xxx][yyy][zzz] = 1;
			else
				profile[xxx][yyy][zzz] = 0;
                }



	afterheader = lseek( dcd, (off_t)(0), SEEK_CUR );

	if ( VERBOSE )
	printf("Calculating surface metric for %d atoms\n", nofCAs);

	if ( FIRST > 1 )
		if ( lseek( dcd, (off_t)(bytes_per_set * (off_t)(FIRST-1)), SEEK_CUR ) == (off_t)(-1) )
			{
				printf("\033[31m\033[1mRequested frame not present ? Abort.\033[0m\n");
				myexit(1);
						}
						

						/* Mark current position */
	start = lseek( dcd, (off_t)(0), SEEK_CUR );

	entered = 0;
	frame = firstframe;
	if ( VERBOSE )
	printf("Now processing frame %8d", frame);
	while( frame <= LAST )
		{
		if ( (unsigned int)(read( dcd, (void *)(&dcd_frame[1]), (size_t)(bytes_per_set) )) != bytes_per_set )
			{
				if ( VERBOSE )
				printf("%8d", (frame-1) );
				if ( frame == FIRST )
					{
						printf("\033[31m\033[1m\nRequested frame not present ? Abort.\033[0m\n");
						myexit(1);
								}
				if ( VERBOSE )
				printf("\nEnd of DCD reached.\n");
				break;
									}
		sprintf( framestring, "%d", frame );

		if ( (frame-firstframe) % STEP == 0 )
		{		
		entered++;		
		build_CAs( (int)(nofatoms) + 2);


		/*******************************************/						
		/* Get maximal dimensions                  */
		/*******************************************/						

		minx = CAs[0][0];
		maxx = CAs[0][0];
		miny = CAs[0][1];
		maxy = CAs[0][1];
		minz = CAs[0][2];
		maxz = CAs[0][2];

		for ( i=0 ; i < nofCAs ; i++ )
			{
				dx = CAs[i][0];
				dy = CAs[i][1];
				dz = CAs[i][2];
		
				if ( dx > maxx )
					maxx = dx;
				else if ( dx < minx )
					minx = dx;
				if ( dy > maxy )
					maxy = dy;
				else if ( dy < miny )
					miny = dy;
				if ( dz > maxz )
					maxz = dz;
				else if ( dz < minz )
					minz = dz;
			}

		dim_x = maxx - minx;
		dim_y = maxy - miny;
		dim_z = maxz - minz;


									/* Grid step 0.4 Angstrom */
		grid_x = (int)((dim_x+8.0) / 0.40 + 0.50 );
		grid_y = (int)((dim_y+8.0) / 0.40 + 0.50 );
		grid_z = (int)((dim_z+8.0) / 0.40 + 0.50 );


									/* Allocate & clear memory for ED map */
		ed = int3tensor( 1, grid_x, 1, grid_y, 1, grid_z );



		/******************/
		/* Build ED  map  */
		/******************/

		for ( i=0 ; i < nofCAs ; i++ )
			{
				dx = CAs[i][0] - minx;
				dy = CAs[i][1] - miny;
				dz = CAs[i][2] - minz;

				xint = (int)((dx+4.0) / 0.40 + 0.50 );
				yint = (int)((dy+4.0) / 0.40 + 0.50 );
				zint = (int)((dz+4.0) / 0.40 + 0.50 );


				if ( 	xint < 8 || yint < 8 || zint < 8 ||
					xint > grid_x-9 || yint > grid_y-9 || zint > grid_z-9 )
					{
						printf("\033[31m\033[1m\nSurface bug: index outside range (%d %d %d) ? Abort.\033[0m\n",
								xint, yint, zint );
						myexit(1);
								}

				for ( xxx = xint-8 ; xxx <= xint+8 ; xxx++ )
				for ( yyy = yint-8 ; yyy <= yint+8 ; yyy++ )
				for ( zzz = zint-8 ; zzz <= zint+8 ; zzz++ )
					ed[xxx][yyy][zzz] |= profile[xxx-xint+8][yyy-yint+8][zzz-zint+8];

				
						}



/*
		for ( xxx = 1 ; xxx <= grid_x ; xxx++ )
		{
		printf("\n\n");
		for ( yyy = 1 ; yyy <= grid_y ; yyy++ )
		{
		for ( zzz = 1 ; zzz <= grid_z ; zzz++ )
			{
				if ( ed[xxx][yyy][zzz] > 0.1 )
					printf("1");
				else
					printf("0");
			}
		printf("\n");
		}
		}
*/


		/**************************************************************************************************/
		/* Estimate surface area from number of 'protein' grid points surrounded by 'solvent' grid points */
		/**************************************************************************************************/

		sum = 0.0;
		for ( o = 2 ; o <  grid_x ; o++ )
		for ( p = 2 ; p <  grid_y ; p++ )
		for ( q = 2 ; q <  grid_z ; q++ )
			if ( ed[o][p][q] )
			{
			aver = 	ed[o][p][q]+ed[o][p][q+1]+ed[o][p][q-1]+
				ed[o][p+1][q]+ed[o][p+1][q+1]+ed[o][p+1][q-1]+
				ed[o][p-1][q]+ed[o][p-1][q+1]+ed[o][p-1][q-1]+
				ed[o+1][p][q]+ed[o+1][p][q+1]+ed[o+1][p][q-1]+
                                ed[o+1][p+1][q]+ed[o+1][p+1][q+1]+ed[o+1][p+1][q-1]+
                                ed[o+1][p-1][q]+ed[o+1][p-1][q+1]+ed[o+1][p-1][q-1]+
				ed[o-1][p][q]+ed[o-1][p][q+1]+ed[o-1][p][q-1]+
                                ed[o-1][p+1][q]+ed[o-1][p+1][q+1]+ed[o-1][p+1][q-1]+
                                ed[o-1][p-1][q]+ed[o-1][p-1][q+1]+ed[o-1][p-1][q-1];

			if ( aver < 26.2 )
					sum += 0.1360;
			}	

		fprintf(proj, "%7d %10d\n", frame, (int)(sum) );

		free_int3tensor( ed,  1, grid_x, 1, grid_y, 1, grid_z );


		if ( STEP > 1 )
			{
				if ( lseek( dcd, (off_t)(bytes_per_set * (off_t)(STEP-1)), SEEK_CUR ) == (off_t)(-1) )
				{
					printf("\033[31m\033[1mRequested frame not present ? Abort.\033[0m\n");
					myexit(1);
							}
				frame += (STEP-1);
			}

		}
		frame++;
		if ( VERBOSE )
		printf("%8d", frame );


						}

	if ( frame == LAST+1 )
		{
		if ( VERBOSE )
		printf("%8d\n", (frame-1) );
		}

#ifndef WINDOWS
	if ( VERBOSE )
		{
		end_timer = time(NULL);
		printf("\033[32m\033[1mAll done in %1.1f minutes.\033[0m\n", (float)(end_timer-start_timer)/60.0 );
		}
#endif
	
	
	fclose( proj );
	myexit( 0 );

}







/*****************************************************************************************************************************/
/**	This is the radius of gyration calculation									    **/
/*****************************************************************************************************************************/



	if ( GYRATION == YES )
	{	
	FILE 	*proj;
	float	aver_x, aver_y, aver_z;
	float	mass, tot_mass;
	float	sum, dx, dy, dz, dist;


	proj = fopen( "carma.Rgyration.dat", "w");
	if ( proj == NULL )
		{	
			printf("\033[31m\033[1mCan not open output file. Abort.\033[0m\n");
			myexit(1);
					}
	

	afterheader = lseek( dcd, (off_t)(0), SEEK_CUR );

	if ( VERBOSE )
	printf("Calculating mass-weighted Rg for %d atoms\n", nofCAs);

	if ( FIRST > 1 )
		if ( lseek( dcd, (off_t)(bytes_per_set * (off_t)(FIRST-1)), SEEK_CUR ) == (off_t)(-1) )
			{
				printf("\033[31m\033[1mRequested frame not present ? Abort.\033[0m\n");
				myexit(1);
						}
						

						/* Mark current position */
	start = lseek( dcd, (off_t)(0), SEEK_CUR );

	entered = 0;
	frame = firstframe;
	if ( VERBOSE )
	printf("Now processing frame %8d", frame);
	while( frame <= LAST )
		{
		if ( (unsigned int)(read( dcd, (void *)(&dcd_frame[1]), (size_t)(bytes_per_set) )) != bytes_per_set )
			{
				if ( VERBOSE )
				printf("%8d", (frame-1) );
				if ( frame == FIRST )
					{
						printf("\033[31m\033[1m\nRequested frame not present ? Abort.\033[0m\n");
						myexit(1);
								}
				if ( VERBOSE )
				printf("\nEnd of DCD reached.\n");
				break;
									}
		sprintf( framestring, "%d", frame );

		if ( (frame-firstframe) % STEP == 0 )
		{		
		entered++;		
		build_CAs( (int)(nofatoms) + 2);


		/******************/
		/* Center of mass */
		/******************/
		
		aver_x = 0.0;
		aver_y = 0.0;
		aver_z = 0.0;
		tot_mass = 0.0;
		for ( i=0 ; i < nofCAs ; i++ )
			{
				mass = masses[i];
				tot_mass += mass;
				aver_x += CAs[i][0] * mass;
				aver_y += CAs[i][1] * mass;
				aver_z += CAs[i][2] * mass;
						}

		aver_x /= tot_mass;			
		aver_y /= tot_mass;			
		aver_z /= tot_mass;			

		/******************/
		/* Rg		  */
		/******************/
		
		sum = 0.0;
		for ( i=0 ; i < nofCAs ; i++ )
			{
				dx = CAs[i][0] - aver_x;
				dy = CAs[i][1] - aver_y;
				dz = CAs[i][2] - aver_z;

				dist = sqrt( dx*dx + dy*dy + dz*dz);
				sum += masses[i] * dist * dist;

						}


		fprintf(proj, "%8d %9.4f\n", frame, sqrt( sum / tot_mass ));


		if ( STEP > 1 )
			{
				if ( lseek( dcd, (off_t)(bytes_per_set * (off_t)(STEP-1)), SEEK_CUR ) == (off_t)(-1) )
				{
					printf("\033[31m\033[1mRequested frame not present ? Abort.\033[0m\n");
					myexit(1);
							}
				frame += (STEP-1);
			}

		}
		frame++;
		if ( VERBOSE )
		printf("%8d", frame );


						}

	if ( frame == LAST+1 )
		{
		if ( VERBOSE )
		printf("%8d\n", (frame-1) );
		}


#ifndef WINDOWS
	if ( VERBOSE )
		{
		end_timer = time(NULL);
		printf("\033[32m\033[1mAll done in %1.1f minutes.\033[0m\n", (float)(end_timer-start_timer)/60.0 );
		}
#endif

	
	fclose( proj );
	myexit( 0 );

}




/*****************************************************************************************************************************/
/**	Export selected frames as PDB files										    **/
/*****************************************************************************************************************************/



	if ( WRITE_PDB == YES )
	{	
	int	HAVE_CHECKED_STRIDE = NO;


	if ( STRIDE == YES )
		system("/bin/rm -f carma.stride.dat");

	afterheader = lseek( dcd, (off_t)(0), SEEK_CUR );

	if ( VERBOSE && STRIDE == NO )
		printf("Exporting selected atoms on selected frames as PDB files\n");

	if ( VERBOSE && STRIDE == YES )
		printf("\033[33mWill attempt to produce secondary structures using STRIDE.\033[0m\n");

	if ( ((float)(min2(headerframes, LAST)) - firstframe +1.0)/(float)(STEP) > 100.0 && STRIDE == NO )
		{
		printf("\033[31m\033[1mIf the DCD header is correct, this will create %d PDB files.\033[0m\n", 
				(int)(((float)(min2(headerframes, LAST)) - firstframe +1.0)/(float)(STEP)) );
#ifndef WINDOWS
		sleep(2);
#endif
		}

	if ( FIRST > 1 )
		if ( lseek( dcd, (off_t)(bytes_per_set * (off_t)(FIRST-1)), SEEK_CUR ) == (off_t)(-1) )
			{
				printf("\033[31m\033[1mRequested frame not present ? Abort.\033[0m\n");
				myexit(1);
						}
						

						/* Mark current position */
	start = lseek( dcd, (off_t)(0), SEEK_CUR );

	entered = 0;
	frame = firstframe;
	if ( VERBOSE )
	printf("Now processing frame %8d", frame);
	while( frame <= LAST )
		{
		if ( (unsigned int)(read( dcd, (void *)(&dcd_frame[1]), (size_t)(bytes_per_set) )) != bytes_per_set )
			{
				if ( VERBOSE )
				printf("%8d", (frame-1) );
				if ( frame == FIRST )
					{
						printf("\033[31m\033[1m\nRequested frame not present ? Abort.\033[0m\n");
						myexit(1);
								}
				if ( VERBOSE )
				printf("\nEnd of DCD reached.\n");
				break;
									}
		sprintf( framestring, "%d", frame );

		if ( (frame-firstframe) % STEP == 0 )
		{		
		FILE    *outPDB;

		entered++;		
		build_CAs( (int)(nofatoms) + 2);

		sprintf( frameno, ".%07d", frame );
		strcpy( filename, strrchr( argv[HAVE_DCD], '/') != NULL ? strrchr( argv[HAVE_DCD], '/') + 1 : argv[HAVE_DCD] );
		strcat( filename, frameno );
		strcat( filename, ".pdb" );

		outPDB = fopen( filename, "w");
		if ( outPDB == NULL )
			{	
				printf("\033[31m\033[1mCan not open output file. Abort.\033[0m\n");
				myexit(1);
						}

		if ( HAVE_CELL == YES )
			fprintf(outPDB,"CRYST1%9.3f%9.3f%9.3f%7.2f%7.2f%7.2f P 1           1\n", 
					cell_a, cell_b, cell_c, cell_alpha, cell_beta, cell_gamma );

		for ( i=0 ; i < nofCAs ; i++ )
			fprintf(outPDB, "ATOM% 7d  %s %s %s%4d    % 8.3f% 8.3f% 8.3f  1.00  0.00\n", 
				i+1, str_atname[i], str_resname[i], str_segname[i], str_resid[i],
				CAs[i][0], CAs[i][1], CAs[i][2] );

		fprintf( outPDB, "END\n");
		fclose( outPDB );

		if ( STRIDE == YES )
		{
		char	comm[3000];


		if ( HAVE_CHECKED_STRIDE == NO )
		{
			int check;
			
			check = system("which stride");
			if ( check != 0 )
				{
					printf("\033[31m\033[1m\n\nAttempt to use stride failed. Abort.\033[0m\n");
					myexit(1);
				}
			HAVE_CHECKED_STRIDE = YES;
		}

		
		sprintf( comm, "stride %s 2>&1 | grep '^[SN][To][R ]' | awk -F '\n' '{ if ( substr($1,1,11) == \"No hydrogen\" ) print \"No hydrogen bonds found in frame \"; else print substr($1,11,50); }' | tr -d '\n' >> carma.stride.dat ; echo \" %10d \" >> carma.stride.dat ; /bin/rm %s", filename, frame, filename);
		system( comm );
		
		
		}


		if ( STEP > 1 )
			{
				if ( lseek( dcd, (off_t)(bytes_per_set * (off_t)(STEP-1)), SEEK_CUR ) == (off_t)(-1) )
				{
					printf("\033[31m\033[1mRequested frame not present ? Abort.\033[0m\n");
					myexit(1);
							}
				frame += (STEP-1);
			}

		}
		frame++;
		if ( VERBOSE )
		printf("%8d", frame );


						}

	if ( frame == LAST+1 )
		{
		if ( VERBOSE )
		printf("%8d\n", (frame-1) );
		}



#ifndef WINDOWS
	if ( VERBOSE )
		{
		end_timer = time(NULL);
		printf("\033[32m\033[1m\nAll done in %1.1f minutes.\033[0m\n", (float)(end_timer-start_timer)/60.0 );
		}
#endif
	
	myexit( 0 );

}






/*****************************************************************************************************************************/
/**	This is the variance-covariance matrix calculation								    **/
/*****************************************************************************************************************************/



	if ( FIND_COV == YES )
	{	
	float	*CAxyz;
	float	*averCAxyz;


/*****************************************************************************************************************************/
/**   Calculate average x,y,z for all CA atoms						                                    **/
/*****************************************************************************************************************************/

	averCAxyz = vector( 1, 3*nofCAs );
	CAxyz     = vector( 1, 3*nofCAs );
	for ( i=1 ; i <= 3*nofCAs ; i++ )
		{
			CAxyz[i] = 0.0;
			averCAxyz[i] = 0.0;
						}
								

	if ( USE_DOT == NO )
	{
	D2 = matrix( 1, 3*nofCAs, 1, 3*nofCAs);
	pD2 = &D2[1][1];
	for ( i=0 ; i < 9*nofCAs*nofCAs ; i++ )
			pD2[i] = 0.0;
	}
	else
	{
	D2 = matrix( 1, nofCAs, 1, nofCAs);
	pD2 = &D2[1][1];
	for ( i=0 ; i < nofCAs*nofCAs ; i++ )
			pD2[i] = 0.0;
	
	}
	
	afterheader = lseek( dcd, (off_t)(0), SEEK_CUR );

	if ( VERBOSE )
	printf("First pass to determine average x,y,z coordinates for %d atoms\n", nofCAs);

	if ( FIRST > 1 )
		if ( lseek( dcd, (off_t)(bytes_per_set * (off_t)(FIRST-1)), SEEK_CUR ) == (off_t)(-1) )
			{
				printf("\033[31m\033[1mRequested frame not present ? Abort.\033[0m\n");
				myexit(1);
						}
						

						/* Mark current position */
	start = lseek( dcd, (off_t)(0), SEEK_CUR );

	entered = 0;
	frame = firstframe;
	if ( VERBOSE )
	printf("Now processing frame %8d", frame);
	while( frame <= LAST )
		{
		if ( (unsigned int)(read( dcd, (void *)(&dcd_frame[1]), (size_t)(bytes_per_set) )) != bytes_per_set )
			{
				if ( VERBOSE )
				printf("%8d", (frame-1) );
				if ( frame == FIRST )
					{
						printf("\033[31m\033[1m\nRequested frame not present ? Abort.\033[0m\n");
						myexit(1);
								}
				if ( VERBOSE )
				printf("\nEnd of DCD reached.\n");
				break;
									}
		sprintf( framestring, "%d", frame );

		if ( (frame-firstframe) % STEP == 0 )
		{		
		entered++;		
		build_CAs( (int)(nofatoms) + 2);

		for ( i=0 ; i < nofCAs ; i++ )
			{
				averCAxyz[i*3+1] += CAs[i][0];
				averCAxyz[i*3+2] += CAs[i][1];
				averCAxyz[i*3+3] += CAs[i][2];
						}
		if ( STEP > 1 )
			{
				if ( lseek( dcd, (off_t)(bytes_per_set * (off_t)(STEP-1)), SEEK_CUR ) == (off_t)(-1) )
				{
					printf("\033[31m\033[1mRequested frame not present ? Abort.\033[0m\n");
					myexit(1);
							}
				frame += (STEP-1);
			}
			
		}
		frame++;
		if ( VERBOSE )
		printf("%8d", frame );


						}

	if ( frame == LAST+1 )
		{
		if ( VERBOSE )
		printf("%8d\n", (frame-1) );
		}
	
	totentered = entered;
	
	if ( VERBOSE )						
	printf("%d frames entered the calculation.\n", entered );

	for ( i=1 ; i <= 3*nofCAs ; i++ )
		averCAxyz[i] /= (float)(entered);





/*****************************************************************************************************************************/
/**   Second pass for displacements	                                                                                    **/
/*****************************************************************************************************************************/



	if ( lseek( dcd, (off_t)(start), SEEK_SET ) == (off_t)(-1) )
		{
			printf("\033[31m\033[1mCan not seek back to the beginning of data ? Abort.\033[0m\n");
			myexit(1);
					}



	if ( VERBOSE )
	printf("Second pass to calculate atomic displacements ...\n");

	if ( USE_DOT == YES )
	{
	rms_aver = fopen( "carma.rms-average.dat", "w");
	if ( rms_aver == NULL )
		{	
			printf("\033[31m\033[1mCan not open output file. Abort.\033[0m\n");
			myexit(1);
		}
	}



	entered = 0;
	frame = firstframe;
	if ( VERBOSE )
	printf("Now processing frame %8d", frame);
	while( frame <= LAST )
		{
		if ( (unsigned int)(read( dcd, (void *)(&dcd_frame[1]), (size_t)(bytes_per_set) )) != bytes_per_set )
			{
				if ( VERBOSE )
				printf("%8d", (frame-1) );
				if ( frame == FIRST )
					{
						if ( VERBOSE )
						printf("\033[31m\033[1m\nRequested frame not present ? Abort.\033[0m\n");
						myexit(1);
								}
				if ( VERBOSE )
				printf("\nEnd of DCD reached. Write variance-covariance map.\n");
				break;
									}
				
		sprintf( framestring, "%d", frame );

		if ( (frame-firstframe) % STEP == 0 )
		{		
		entered++;		
		build_CAs( (int)(nofatoms) + 2);


		for ( i=0 ; i < nofCAs ; i++ )
			{
				CAxyz[i*3+1] = CAs[i][0];
				CAxyz[i*3+2] = CAs[i][1];
				CAxyz[i*3+3] = CAs[i][2];
						}


		/*************************************************************************************/
		/* Since we are here (and we have average coordinates), we might as well             */
		/* write-out a file containing rms deviation from this average                       */
		/*************************************************************************************/
	
		if ( USE_DOT == YES )
		{
		double	sum;
		float	ddx, ddy, ddz;
		float	current_rms;
	
		sum = 0.0;
		for ( i=0 ; i < nofCAs ; i++ )
			{
				ddx = averCAxyz[i*3+1] - CAxyz[i*3+1];
				ddy = averCAxyz[i*3+2] - CAxyz[i*3+2];
				ddz = averCAxyz[i*3+3] - CAxyz[i*3+3];
				sum += ddx*ddx + ddy*ddy + ddz*ddz;
			}
		current_rms = sqrt( sum / (float)(nofCAs) );
	
		fprintf(rms_aver, " % 7d % 9.4f\n", frame, current_rms );
			
		}

									/* averCAxyz[] has the averages */
									/* CAxyz[] has this frame's coordinates */
									/* Use them to populate D2[][] which will */
									/* become the covariance matrix */


		if ( USE_DOT == NO )
		{
		for ( i=1 ; i <= 3*nofCAs ; i++)
		for ( k=i ; k <= 3*nofCAs ; k++)
			D2[i][k] += CAxyz[i]*CAxyz[k] +averCAxyz[i]*averCAxyz[k] -CAxyz[i]*averCAxyz[k] -averCAxyz[i]*CAxyz[k];
		}
		else
		{
		for ( i=1 ; i <= nofCAs ; i++)
		for ( k=i ; k <= nofCAs ; k++)
			D2[i][k] += 	  CAxyz[(i-1)*3+1]*CAxyz[(k-1)*3+1] + averCAxyz[(i-1)*3+1]*averCAxyz[(k-1)*3+1] 
					+ CAxyz[(i-1)*3+2]*CAxyz[(k-1)*3+2] + averCAxyz[(i-1)*3+2]*averCAxyz[(k-1)*3+2]
					+ CAxyz[(i-1)*3+3]*CAxyz[(k-1)*3+3] + averCAxyz[(i-1)*3+3]*averCAxyz[(k-1)*3+3]
                                        - CAxyz[(i-1)*3+2]*averCAxyz[(k-1)*3+2] - averCAxyz[(i-1)*3+2]*CAxyz[(k-1)*3+2]
					- CAxyz[(i-1)*3+1]*averCAxyz[(k-1)*3+1] - averCAxyz[(i-1)*3+1]*CAxyz[(k-1)*3+1]
                                        - CAxyz[(i-1)*3+3]*averCAxyz[(k-1)*3+3] - averCAxyz[(i-1)*3+3]*CAxyz[(k-1)*3+3];
		}

		if ( STEP > 1 )
			{
				if ( lseek( dcd, (off_t)(bytes_per_set * (off_t)(STEP-1)), SEEK_CUR ) == (off_t)(-1) )
				{
					printf("\033[31m\033[1mRequested frame not present ? Abort.\033[0m\n");
					myexit(1);
							}
				frame += (STEP-1);
			}
		}
		frame++;
		if ( VERBOSE )
		printf("%8d", frame );


						}

	if ( frame == LAST+1 && VERBOSE )
		printf("%8d\n", (frame-1) );

	if ( MASSES == YES && VERBOSE )
		printf("Mass-weighting covariance matrix ...\n" );

	if ( USE_DOT == NO )
	{
	for ( i=1 ; i <= 3*nofCAs ; i++)
	for ( k=i ; k <= 3*nofCAs ; k++)
		{
			if ( MASSES == YES )
				D2[i][k] *= ( sqrt(masses[(i-1)/3]) * sqrt(masses[(k-1)/3]) );

			D2[k][i] = D2[i][k];							
				}

	}
	else
	{
	fclose( rms_aver );

	for ( i=1 ; i <= nofCAs ; i++)
	for ( k=i ; k <= nofCAs ; k++)
		{
			if ( MASSES == YES )
				D2[i][k] *= ( sqrt(masses[i-1]) * sqrt(masses[k-1]) );
			D2[k][i] = D2[i][k];
				}
	}
	
	
	totentered = entered;
		
	
	if ( VERBOSE )
	printf("%d frames entered the calculation.\n", entered );


	max = -1000000000000.0 ;
	min =  1000000000000.0 ; 

	if ( USE_DOT == NO )
	{
	for ( i=0 ; i < 9*nofCAs*nofCAs ; i++ )
		{
			pD2[i] = pD2[i] / (float)(entered);
			if ( pD2[i] > max )
				max =  pD2[i];
			if ( pD2[i] < min )
				min =  pD2[i];

						}
							}
	else
	{
	for ( i=0 ; i < nofCAs*nofCAs ; i++ )
		{
			pD2[i] = pD2[i] / (float)(entered);
			if ( pD2[i] > max )
				max =  pD2[i];
			if ( pD2[i] < min )
				min =  pD2[i];

						}
							}
	
	
	sprintf( frameno, ".varcov");
	strcpy( filename, strrchr( argv[HAVE_DCD], '/') != NULL ? strrchr( argv[HAVE_DCD], '/') + 1 : argv[HAVE_DCD] );
	strcat( filename, frameno );
	





	/*************************************************************************************/
	/* Since we are here (and we have average coordinates & variances), we might as well */
	/* write-out a PDB containing the average structure and fluctuations. The catch is   */
	/* that we can only write-out selected atoms                                         */
	/*************************************************************************************/

	if ( USE_DOT == YES )
	{
	FILE	*outPDB;
	int	NEW_STEP;
	
	outPDB = fopen( "carma.average.pdb", "w");
	if ( outPDB == NULL )
		{	
			printf("\033[31m\033[1mCan not open output file. Abort.\033[0m\n");
			myexit(1);
					}


	for ( i=0 ; i < nofCAs ; i++ )
		fprintf(outPDB, "ATOM% 7d  %s %s %s%4d    % 8.3f% 8.3f% 8.3f  1.00% 6.2f\n", 
			i+1, str_atname[i], str_resname[i], str_segname[i], str_resid[i],
			averCAxyz[i*3+1], averCAxyz[i*3+2], averCAxyz[i*3+3],
			sqrt( D2[i+1][i+1] ) );

	fprintf( outPDB, "END\n");
	fclose( outPDB );



	if ( WRITE_SUPER == YES )
	{

	if ( VERBOSE )
	printf("Third pass to prepare PDB with superimposed structures plus RMSFs ...\n");

	
	NEW_STEP = (int)(((float)(min2(headerframes, LAST)) - firstframe +1.0)/500.0);
	if ( NEW_STEP < 1 )
		NEW_STEP = 1;
	
	if ( lseek( dcd, (off_t)(start), SEEK_SET ) == (off_t)(-1) )
		{
			printf("\033[31m\033[1mCan not seek back to the beginning of data ? Abort.\033[0m\n");
			myexit(1);
					}


	outPDB = fopen( "carma.superposition.pdb", "w");
	if ( outPDB == NULL )
		{	
			printf("\033[31m\033[1mCan not open carma.superposition.pdb file. Abort.\033[0m\n");
			myexit(1);
					}

	entered = 0;
	frame = firstframe;
	if ( VERBOSE )
	printf("Now processing frame %8d", frame);
	while( frame <= LAST )
		{
		if ( (unsigned int)(read( dcd, (void *)(&dcd_frame[1]), (size_t)(bytes_per_set) )) != bytes_per_set )
			{
				if ( VERBOSE )
				printf("%8d", (frame-1) );
				if ( frame == FIRST )
					{
						if ( VERBOSE )
						printf("\033[31m\033[1m\nRequested frame not present ? Abort.\033[0m\n");
						myexit(1);
								}
				if ( VERBOSE )
				printf("\nEnd of DCD reached.\n");
				break;
									}
				
		sprintf( framestring, "%d", frame );

		if ( (frame-firstframe) % NEW_STEP == 0 )
		{		
		entered++;		
		build_CAs( (int)(nofatoms) + 2);


		for ( i=0 ; i < nofCAs ; i++ )
			fprintf(outPDB, "ATOM% 7d  %s %s %s%4d    % 8.3f% 8.3f% 8.3f  1.00% 6.2f\n",
				i+1, str_atname[i], str_resname[i], str_segname[i], str_resid[i],
				CAs[i][0], CAs[i][1], CAs[i][2], sqrt( D2[i+1][i+1] ) );
		
		fprintf( outPDB, "END\n");



		if ( NEW_STEP > 1 )
			{
				if ( lseek( dcd, (off_t)(bytes_per_set * (off_t)(NEW_STEP-1)), SEEK_CUR ) == (off_t)(-1) )
				{
					printf("\033[31m\033[1mRequested frame not present ? Abort.\033[0m\n");
					myexit(1);
							}
				frame += (NEW_STEP-1);
			}
		}
		frame++;
		if ( VERBOSE )
		printf("%8d", frame );


						}

	if ( frame == LAST+1 && VERBOSE )
		printf("%8d\n", (frame-1) );


	fclose( outPDB );
	}
	


	}





/*****************************************************************************************************************************/
/**	Cross-correlation needed ? Eigenvalues & vectors needed ?							    **/
/*****************************************************************************************************************************/

	if ( NORMALISE == NO )
	{
		
	if ( VERBOSE )
		{
			printf("Maximum of variance-covariance matrix is %f\n", max );
			printf("Minimum of variance-covariance matrix is %f\n", min );
					}			
					
	REVERSE = !REVERSE ;
	if ( HAVE_MIN == NO )
		gmin = min;
	if ( HAVE_MAX == NO )
		gmax = max;
		



	if ( USE_DOT == NO )
		nofCAs = nofCAs * 3;
		
	wps( D2, filename );

	if ( USE_DOT == NO )
		nofCAs = nofCAs / 3;


#if defined (LAPACK) || defined (NR)
	if ( EIGEN == YES )
	{
	if ( USE_DOT == NO )
		eigendim = nofCAs * 3;
	else
		eigendim = nofCAs;
				
	eigen( D2 );





/*****************************************************************************************************************************/
/**	Third pass to calculate projection of trajectory's fluctuations onto eigenvector				    **/
/*****************************************************************************************************************************/

	if ( EIGENFIRST > 0 )
	{
	FILE 	*proj;
	float	sum;


								/* Allocate a matrix for the DG plots (calcs later on) */
	if ( DG_PLOTS > 0 )
	{
	DG = matrix( 1, totentered, 1, DG_PLOTS );
	}


	proj = fopen( "carma.PCA.fluctuations.dat", "w");
	if ( proj == NULL )
		{	
			printf("\033[31m\033[1mCan not open output file. Abort.\033[0m\n");
			myexit(1);
					}
	
	if ( lseek( dcd, (off_t)(start), SEEK_SET ) == (off_t)(-1) )
		{
			printf("\033[31m\033[1mCan not seek back to the beginning of data ? Abort.\033[0m\n");
			myexit(1);
					}



	if ( VERBOSE )
		{
		printf("Third pass to determine displacements along eigenvectors.\n");
		printf("Chosen eigenvectors are : \n");
		i = 0;
		for ( k=EIGENFIRST ; k <= EIGENLAST ; k += EIGENSTEP )
			{
				printf("%d ", k );
				i++;
				if ( i > 9 )
					{
					i = 0;
					printf("\n");
					}
					}	
		printf("\n");
		}


	entered = 0;
	frame = firstframe;
	if ( VERBOSE )
	printf("Now processing frame %8d", frame);
	while( frame <= LAST )
		{
		if ( (unsigned int)(read( dcd, (void *)(&dcd_frame[1]), (size_t)(bytes_per_set) )) != bytes_per_set )
			{
				if ( VERBOSE )
				printf("%8d", (frame-1) );
				if ( frame == FIRST )
					{
						if ( VERBOSE )
						printf("\033[31m\033[1m\nRequested frame not present ? Abort.\033[0m\n");
						myexit(1);
								}
				if ( VERBOSE )
				printf("\nEnd of DCD reached.\n");
				break;
									}
				
		sprintf( framestring, "%d", frame );

		if ( (frame-firstframe) % STEP == 0 )
		{		
		entered++;	
		if ( entered > totentered )
			{
				printf("\033[31m\033[1m\nThe DCD file is still growing ? Use the \"-last\" flag. Aborting.\033[0m\n");
				myexit( 1 );
			}
	
		build_CAs( (int)(nofatoms) + 2);


		for ( i=0 ; i < nofCAs ; i++ )
			{
				CAxyz[i*3+1] = CAs[i][0]-averCAxyz[i*3+1];
				CAxyz[i*3+2] = CAs[i][1]-averCAxyz[i*3+2];
				CAxyz[i*3+3] = CAs[i][2]-averCAxyz[i*3+3];
						}


		fprintf(proj, "%8d ", frame );
		for ( k=EIGENFIRST ; k <= EIGENLAST ; k += EIGENSTEP )
		{
		sum = 0.0;
		for ( i=1 ; i <= eigendim ; i++ )
			sum += CAxyz[i] * eigenvectors[i][k];
		
		fprintf(proj, "%12.7f ", sum );

		if ( DG_PLOTS > 0 && (k-EIGENFIRST+1) <= DG_PLOTS )
			DG[entered][k-EIGENFIRST+1] = sum;


		}
		fprintf(proj, "\n");
		

		if ( STEP > 1 )
			{
				if ( lseek( dcd, (off_t)(bytes_per_set * (off_t)(STEP-1)), SEEK_CUR ) == (off_t)(-1) )
				{
					printf("\033[31m\033[1mRequested frame not present ? Abort.\033[0m\n");
					myexit(1);
							}
				frame += (STEP-1);
			}
		}
		frame++;
		if ( VERBOSE )
		printf("%8d", frame );


						}

	if ( frame == LAST+1 && VERBOSE )
		printf("%8d\n", (frame-1) );



	/***********************************************************************/
	/* DG[][] contains the fluctuations for each frame and every           */
	/* eigenvector. We bin the data, convert to probabilities (normalise), */
	/* take the logarithms, multiply with kB & temp, and export            */
	/***********************************************************************/

	if ( DG_PLOTS > 0 )
	{
	int 	tframes;
	int	v1, v2, frame;
	int	bins, bins2;
	int	m;	
	float	v1max, v1min, val, limit;
	float	**PLOT;
	float	val1, val2, val3;
	int	pos1, pos2, pos3;
	float	wmax, wsum;


	bins2 = 0;
	tframes = totentered;

/*
	for ( v1 = 1 ; v1 <= tframes ; v1++ )
	for ( v2 = 1 ; v2 <= DG_PLOTS ; v2++ )
		printf(" %6d %6d %12.7f\n", v1, v2, DG[v1][v2] );
*/

	bins = (int)( sqrt( (double)( tframes) ) / 2);		/* number of bins for plot */
	if ( bins < 4 )
		{
			printf("\033[31m\033[1m\nToo few (%d) bins for DeltaG plots. Abort.\033[0m\n", bins);
			myexit(1);
		}
	if ( bins < 30 && VERBOSE )
		{
			printf("\033[31m\033[1m\nWarning: very few (%d) bins for DeltaG plots.\033[0m\n", bins);
		}

								/* Allocate 2D array for plot data */
	PLOT = matrix( 1, bins, 1, bins );


	/* Determine limits of plots */

	v1max = DG[1][1];
	v1min = DG[1][1];
	for ( v1 = 1 ; v1 < tframes ; v1++ )
	for ( v2 = 1 ; v2 <= DG_PLOTS ; v2++ )
		{
			val = DG[v1][v2];
			if ( val > v1max )
				v1max = val;
			if ( val < v1min )
				v1min = val;
		}

	if ( DGLEN < 0.0 )
		limit = 1.20 * max2( fabs( v1max), fabs( v1min));
	else
		limit = DGLEN / 2.0;

	if ( VERBOSE )
		printf("DeltaG plots will extend from %+5.2f to %+5.2f.\n", -limit, limit);


						/* Prepare 3D matrix for cluster analysis */
	if ( DG_PLOTS >= 3 ) 
		{
		bins2 = 2 * (int)((int)( pow( (double)( tframes), 1.0/3.0 ) +0.50) / 2 +0.50);

		CLUSTER = f3tensor( 1, bins2, 1, bins2, 1, bins2 );
		for ( i = 1 ; i <= bins2 ; i++ )
		for ( k = 1 ; k <= bins2 ; k++ )
		for ( m = 1 ; m <= bins2 ; m++ )
			CLUSTER[i][k][m] = 0.0;
		for ( frame = 1 ; frame <= tframes ; frame++ )
			{
				val1 = DG[frame][1];
				val2 = DG[frame][2];
				val3 = DG[frame][3];
		
				pos1 = (int)( bins2 * (val1 + limit) / (2.0*limit) + 0.50 )+1;
				pos2 = (int)( bins2 * (val2 + limit) / (2.0*limit) + 0.50 )+1;
				pos3 = (int)( bins2 * (val3 + limit) / (2.0*limit) + 0.50 )+1;

				CLUSTER[pos1][pos2][pos3] += 1.0;
			}
		}



	REVERSE = !REVERSE ;

	/* The plots in terms of eigenvectors */

	for ( v1 = 1    ; v1 <  DG_PLOTS ; v1++ )
	for ( v2 = v1+1 ; v2 <= DG_PLOTS ; v2++ )
	{
	wsum = 0.0;
	wmax = 0.0;
	for ( i = 1 ; i <= bins ; i++ )
	for ( k = 1 ; k <= bins ; k++ )
		PLOT[i][k] = 0.90;

	for ( frame = 1 ; frame <= tframes ; frame++ )
	{
		val1 = DG[frame][v1];
		val2 = DG[frame][v2];
		
		pos1 = (int)( bins * (val1 + limit) / (2.0*limit) + 0.50 )+1;
		pos2 = (int)( bins * (val2 + limit) / (2.0*limit) + 0.50 )+1;

		PLOT[pos1][pos2] += 1.0;

		if ( PLOT[pos1][pos2] > wmax )
			wmax = PLOT[pos1][pos2];

		wsum += 1.0;
	}

	
	gmax = -1000000000000.0 ;
	gmin =  1000000000000.0 ; 
	for ( i = 1 ; i <= bins ; i++ )
	for ( k = 1 ; k <= bins ; k++ )
		{
			val = - DGCONST * DGTEMP * log( PLOT[i][k] / (double)(wmax) ) ;
			PLOT[i][k] = val;
			if ( val > gmax )
				gmax = val;
			if ( val < gmin )
				gmin = val;
		}

	if ( VERBOSE )
		{
			printf("Maximum of the %02d - %02d DeltaG plot is %f kcal/mol\n", v1, v2, gmax );
					}			

	sprintf( pscomment, "Cartesian PCA DeltaG plot. Vectors %02d - %02d, ranging from %f to %f. DeltaG values: %f to zero.",
			v1, v2, -limit, limit, gmax );


	nofCAs = bins;
	sprintf( filename, "carma.PCA.DG_%02d_%02d", v1, v2 );
	wps( PLOT, filename );


	}

	free_matrix(PLOT, 1, bins, 1, bins );

	if ( DG_PLOTS >= 3 ) 
		cluster( bins2, tframes, limit );


	}

	/*****************     END DG_PLOT          ****************************/


	
#ifndef WINDOWS
	if ( VERBOSE )
		{
		end_timer = time(NULL);
		printf("\033[32m\033[1mAll done in %1.1f minutes.\033[0m\n", (float)(end_timer-start_timer)/60.0 );
		}
#endif
	
	fclose( proj );
	myexit( 0 );
	

	
	}






/*****************************************************************************************************************************/
/**	... or, third pass to calculate projection of trajectory onto eigenvector					    **/
/*****************************************************************************************************************************/

	else if ( EIGENFIRST_W > 0 )
	{
	int	outdcd;
	char	*outdcdhead;
	float	sum;
	float	*intermed;

	
	if ( EIGENFIRST_W > 0 && (EIGENFIRST_W > eigendim || EIGENLAST_W > eigendim ))
		{
			printf("\033[31m\033[1mA requested eigenvector does not exist.\033[0m\n");
			myexit( 1 );
					}
	if ( EIGENFIRST_W > 0 && USE_DOT == YES )
		{
			printf("\033[31m\033[1mCan not do eigenvector projection with \"-dot\" products.\033[0m\n");
			exit ( 1 );
					}
					


/* Quick and dirty : open output dcd, copy everything as is up to the start of data from the input file, */
/* and then start modifying the CA coordinates only and writing out the whole block */


#ifdef WINDOWS
	outdcd = open( "carma.proj.dcd", O_WRONLY | O_CREAT | O_TRUNC | O_BINARY | O_RANDOM, S_IRUSR | S_IWUSR );
#else
	outdcd = open( "carma.proj.dcd", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP );
#endif
	if ( outdcd == -1 )
		{
			printf("\033[31m\033[1mCan not open DCD file for output. Abort.\033[0m\n");
			myexit( 1 );
					}

	outdcdhead = malloc( (size_t)(afterheader) );
	if ( lseek( dcd, (off_t)(0), SEEK_SET ) == (off_t)(-1) )
		{
			printf("\033[31m\033[1mCan not seek back to the beginning of file ? Abort.\033[0m\n");
			myexit(1);
					}
	
	if ( (off_t)(read( dcd, outdcdhead, (size_t)(afterheader) )) != afterheader )
		{
			printf("\033[31m\033[1mPremature EOF for DCD file ? Abort.\033[0m\n");
			myexit(1);
					}

	if ( WRITE_CAS == YES )
		*((unsigned int *)(&outdcdhead[afterheader-8])) = (unsigned int)(nofCAs);

	if ( (off_t)(write( outdcd, outdcdhead, (size_t)(afterheader) )) != afterheader )
		{
			printf("\033[31m\033[1mFailed to write header block to DCD file ? Abort.\033[0m\n");
			myexit(1);
					}
	if ( lseek( dcd, (off_t)(start), SEEK_SET ) == (off_t)(-1) )
		{
			printf("\033[31m\033[1mCan not seek back to the beginning of data ? Abort.\033[0m\n");
			myexit(1);
					}



	if ( VERBOSE )
		{
		printf("Third pass to project trajectory onto eigenvectors.\n");
		printf("Chosen eigenvectors are : \n");
		i = 0;
		for ( k=EIGENFIRST_W ; k <= EIGENLAST_W ; k += EIGENSTEP_W )
			{
				printf("%d ", k );
				i++;
				if ( i > 9 )
					{
					i = 0;
					printf("\n");
					}
					}	
		printf("\n");
		}



	intermed = vector( 1, 3*nofCAs );

	entered = 0;
	frame = firstframe;
	if ( VERBOSE )
	printf("Now processing frame %8d", frame);
	while( frame <= LAST )
		{
		if ( (unsigned int)(read( dcd, (void *)(&dcd_frame[1]), (size_t)(bytes_per_set) )) != bytes_per_set )
			{
				if ( VERBOSE )
				printf("%8d", (frame-1) );
				if ( frame == FIRST )
					{
						if ( VERBOSE )
						printf("\033[31m\033[1m\nRequested frame not present ? Abort.\033[0m\n");
						myexit(1);
								}
				if ( VERBOSE )
				printf("\nEnd of DCD reached.\n");
				break;
									}
				
		sprintf( framestring, "%d", frame );

		if ( (frame-firstframe) % STEP == 0 )
		{		
		build_CAs( (int)(nofatoms) + 2);
		entered++;

		for ( i=0 ; i < nofCAs ; i++ )
			{
				CAxyz[i*3+1] = CAs[i][0]-averCAxyz[i*3+1];
				CAxyz[i*3+2] = CAs[i][1]-averCAxyz[i*3+2];
				CAxyz[i*3+3] = CAs[i][2]-averCAxyz[i*3+3];
						}

		for ( i=1 ; i <= 3*nofCAs ; i++ )
			intermed[i] = 0;

		for ( k=EIGENFIRST_W ; k <= EIGENLAST_W ; k += EIGENSTEP_W )
		{
		sum = 0.0;
		for ( i=1 ; i <= eigendim ; i++ )
			sum += CAxyz[i] * eigenvectors[i][k];
		

		for ( i=0 ; i < nofCAs ; i++ )
			{
				intermed[i*3+1] += sum * eigenvectors[i*3+1][k];
				intermed[i*3+2] += sum * eigenvectors[i*3+2][k];
				intermed[i*3+3] += sum * eigenvectors[i*3+3][k];
						}

		}


		for ( i=0 ; i < nofCAs ; i++ )
			{
				CAs[i][0] = (float)(averCAxyz[i*3+1] + intermed[i*3+1]) ;
				CAs[i][1] = (float)(averCAxyz[i*3+2] + intermed[i*3+2]) ;
				CAs[i][2] = (float)(averCAxyz[i*3+3] + intermed[i*3+3]) ;
						}
		
		
		if ( WRITE_CAS == YES )
			{
			write_CAs2( (int)(nofCAs) + 2);
		
			if ( (unsigned int)(write( outdcd, (void *)(&wdcd_frame[1]), (size_t)(wbytes_per_set) )) != wbytes_per_set )
				{
					printf("\033[31m\033[1mFailed to write frame %d to DCD file.\033[0m\n", frame );
					myexit(1);
							}
								}
		else
			{	
			write_CAs( (int)(nofatoms) + 2);
		
			if ( (unsigned int)(write( outdcd, (void *)(&dcd_frame[1]), (size_t)(bytes_per_set) )) != bytes_per_set )
				{
					printf("\033[31m\033[1mFailed to write frame %d to DCD file.\033[0m\n", frame );
					myexit(1);
							}
								}
		if ( STEP > 1 )
			{
				if ( lseek( dcd, (off_t)(bytes_per_set * (off_t)(STEP-1)), SEEK_CUR ) == (off_t)(-1) )
				{
					printf("\033[31m\033[1mRequested frame not present ? Abort.\033[0m\n");
					myexit(1);
							}
				frame += (STEP-1);
			}
								
		}
		frame++;
		if ( VERBOSE )
		printf("%8d", frame );


						}

	if ( frame == LAST+1 && VERBOSE )
		printf("%8d\n", (frame-1) );

	
	close( outdcd );
	
#ifndef WINDOWS
	if ( VERBOSE )
		{
		end_timer = time(NULL);
		printf("\033[32m\033[1mAll done in %1.1f minutes.\033[0m\n", (float)(end_timer-start_timer)/60.0 );
		}
#endif
	
	myexit( 0 );
	

	

	}


/*****************************************************************************************************************************/
/**	... or, third pass to construct an artificial trajectory							    **/
/*****************************************************************************************************************************/

	else if ( ART_EIGEN > 0 )
	{
	int	outdcd;
	char	*outdcdhead;
	float	sum;
	float	*intermed;
	float	*fluct_proj;
	FILE 	*proj;
	int	frames_from_fluct;


	
	if ( ART_EIGEN > eigendim )
		{
			printf("\033[31m\033[1mToo many eigenvectors requested.\033[0m\n");
			myexit( 1 );
					}
	if ( USE_DOT == YES )
		{
			printf("\033[31m\033[1mCan not construct artificial trajectory with \"-dot\" products.\033[0m\n");
			exit ( 1 );
					}
					

/* What we do here is to open a pre-existing carma.fluctuations.dat file from which we will read abs(min,max) amplitudes for */
/* each eigenvector. We will then construct an artificial trajectory using as amplitudes (for each eigenvector) a randomly */
/* chosen value from the given range */

	proj = fopen( "carma.fluctuations.dat", "r");
	if ( proj == NULL )
		{	
			printf("\033[31m\033[1mCan not open the 'carma.fluctuations.dat' file. Abort.\033[0m\n");
			myexit(1);
					}
					
	fluct_proj = vector( 1, ART_EIGEN );
	
	for ( i=1 ; i <= ART_EIGEN ; i++ )
	          fluct_proj[i] = -1.0;
	  
	while ( fscanf( proj, "%d", &frames_from_fluct) != EOF )
	          {
	                  for (i=1 ; i <= ART_EIGEN ; i++ )
	                          {
	                                  if ( fscanf( proj, "%f", &sum ) == EOF )
	                                          {
	                                          printf("\033[31m\033[1mUnexpected end-of-file for 'carma.fluctuations.dat'. Abort.\033[0m\n");
	                                          exit ( 1 );
	                                          }
                          if ( fabs( sum ) > fluct_proj[i] )
                          fluct_proj[i] = fabs( sum );
                                  }
                  } 
	fclose( proj );

/* Quick and dirty : open output dcd, copy everything as is up to the start of data from the input file, */
/* and then start modifying the CA coordinates only and writing out the whole block */


#ifdef WINDOWS
	outdcd = open( "carma.arti.dcd", O_WRONLY | O_CREAT | O_TRUNC | O_BINARY | O_RANDOM, S_IRUSR | S_IWUSR );
#else
	outdcd = open( "carma.arti.dcd", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP );
#endif
	if ( outdcd == -1 )
		{
			printf("\033[31m\033[1mCan not open DCD file for output. Abort.\033[0m\n");
			myexit( 1 );
					}

	outdcdhead = malloc( (size_t)(afterheader) );
	if ( lseek( dcd, (off_t)(0), SEEK_SET ) == (off_t)(-1) )
		{
			printf("\033[31m\033[1mCan not seek back to the beginning of file ? Abort.\033[0m\n");
			myexit(1);
					}
	
	if ( (off_t)(read( dcd, outdcdhead, (size_t)(afterheader) )) != afterheader )
		{
			printf("\033[31m\033[1mPremature EOF for DCD file ? Abort.\033[0m\n");
			myexit(1);
					}

	if ( WRITE_CAS == YES )
		*((unsigned int *)(&outdcdhead[afterheader-8])) = (unsigned int)(nofCAs);


	*((unsigned int *)(&outdcdhead[8])) = (unsigned int)(ART_FRAMES);


	if ( (off_t)(write( outdcd, outdcdhead, (size_t)(afterheader) )) != afterheader )
		{
			printf("\033[31m\033[1mFailed to write header block to DCD file ? Abort.\033[0m\n");
			myexit(1);
					}
	if ( lseek( dcd, (off_t)(start), SEEK_SET ) == (off_t)(-1) )
		{
			printf("\033[31m\033[1mCan not seek back to the beginning of data ? Abort.\033[0m\n");
			myexit(1);
					}



	if ( VERBOSE )
		{
		printf("Constructing artificial trajectory.\n");
		printf("Chosen eigenvectors and corresponding maximum amplitudes are : \n");
		for ( k=1 ; k <= ART_EIGEN ; k++ )
			printf("%4d %12.7f\n", k, fluct_proj[k] );
                  }
                  

	intermed = vector( 1, 3*nofCAs );

	frame = 1;
	if ( VERBOSE )
	printf("Now writing frame %6d", frame);
	while( frame <= ART_FRAMES )
		{

		for ( i=1 ; i <= 3*nofCAs ; i++ )
			intermed[i] = 0;


		for ( k=1 ; k <= ART_EIGEN ; k++ )
		{

		sum = 2.0 * (0.50 - getrand) * fluct_proj[k]; 

		for ( i=0 ; i < nofCAs ; i++ )
			{
				intermed[i*3+1] += sum * eigenvectors[i*3+1][k];
				intermed[i*3+2] += sum * eigenvectors[i*3+2][k];
				intermed[i*3+3] += sum * eigenvectors[i*3+3][k];
						}
							}


		for ( i=0 ; i < nofCAs ; i++ )
			{
				CAs[i][0] = (float)(averCAxyz[i*3+1] + intermed[i*3+1]) ;
				CAs[i][1] = (float)(averCAxyz[i*3+2] + intermed[i*3+2]) ;
				CAs[i][2] = (float)(averCAxyz[i*3+3] + intermed[i*3+3]) ;
						}
		
		
		if ( WRITE_CAS == YES )
			{
			write_CAs2( (int)(nofCAs) + 2);
		
			if ( (unsigned int)(write( outdcd, (void *)(&wdcd_frame[1]), (size_t)(wbytes_per_set) )) != wbytes_per_set )
				{
					printf("\033[31m\033[1mFailed to write frame %d to DCD file.\033[0m\n", frame );
					myexit(1);
							}
								}
		else
			{	
			write_CAs( (int)(nofatoms) + 2);
		
			if ( (unsigned int)(write( outdcd, (void *)(&dcd_frame[1]), (size_t)(bytes_per_set) )) != bytes_per_set )
				{
					printf("\033[31m\033[1mFailed to write frame %d to DCD file.\033[0m\n", frame );
					myexit(1);
							}
								}
								
		frame++;
		if ( VERBOSE )
		printf("%8d", frame );


						}

	if ( frame == ART_FRAMES+1 && VERBOSE )
		printf("%8d\n", (frame-1) );

	
	close( outdcd );

#ifndef WINDOWS	
	if ( VERBOSE )
		{
		end_timer = time(NULL);
		printf("\033[32m\033[1mAll done in %1.1f minutes.\033[0m\n", (float)(end_timer-start_timer)/60.0 );
		}
#endif
	
	myexit( 0 );
	

	

	}




/*****************************************************************************************************************************/
/**	... or, third pass to calculate ("play") a trajectory for the projection onto eigenvector			    **/
/*****************************************************************************************************************************/

	else if ( EIGENPLAY > 0 )
	{
	int	outdcd;
	char	*outdcdhead;
	float	sum;
	float	*intermed;
	


	
	if ( EIGENPLAY > eigendim )
		{
			printf("\033[31m\033[1mA requested eigenvector does not exist.\033[0m\n");
			myexit( 1 );
					}


/* Quick and dirty : open output dcd, copy everything as is up to the start of data from the input file, */
/* and then start modifying the CA coordinates only and writing out the whole block */

#ifdef WINDOWS
	outdcd = open( "carma.play.dcd", O_WRONLY | O_CREAT | O_TRUNC | O_BINARY | O_RANDOM, S_IRUSR | S_IWUSR );
#else
	outdcd = open( "carma.play.dcd", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP );
#endif
	if ( outdcd == -1 )
		{
			printf("\033[31m\033[1mCan not open DCD file for output. Abort.\033[0m\n");
			myexit( 1 );
					}

	outdcdhead = malloc( (size_t)(afterheader) );
	if ( lseek( dcd, (off_t)(0), SEEK_SET ) == (off_t)(-1) )
		{
			printf("\033[31m\033[1mCan not seek back to the beginning of file ? Abort.\033[0m\n");
			myexit(1);
					}
	if ( (off_t)(read( dcd, outdcdhead, (size_t)(afterheader) )) != afterheader )
		{
			printf("\033[31m\033[1mPremature EOF for DCD file ? Abort.\033[0m\n");
			myexit(1);
					}

	if ( WRITE_CAS == YES )
		*((unsigned int *)(&outdcdhead[afterheader-8])) = (unsigned int)(nofCAs);

	if ( (off_t)(write( outdcd, outdcdhead, (size_t)(afterheader) )) != afterheader )
		{
			printf("\033[31m\033[1mFailed to write header block to DCD file ? Abort.\033[0m\n");
			myexit(1);
					}
	if ( lseek( dcd, (off_t)(start), SEEK_SET ) == (off_t)(-1) )
		{
			printf("\033[31m\033[1mCan not seek back to the beginning of data ? Abort.\033[0m\n");
			myexit(1);
					}



	if ( VERBOSE )
		printf("Third pass to contruct a trajectory of the motion on an eigenvector.\n");


	PLAYING = YES;
	intermed = vector( 1, 3*nofCAs );

	entered = 0;
	frame = firstframe;
	if ( VERBOSE )
	printf("Now processing frame %8d", frame);
	while( frame <= LAST )
		{
		if ( (unsigned int)(read( dcd, (void *)(&dcd_frame[1]), (size_t)(bytes_per_set) )) != bytes_per_set )
			{
				if ( VERBOSE )
				printf("%8d", (frame-1) );
				if ( frame == FIRST )
					{
						if ( VERBOSE )
						printf("\033[31m\033[1m\nRequested frame not present ? Abort.\033[0m\n");
						myexit(1);
								}
				if ( VERBOSE )
				printf("\nEnd of DCD reached.\n");
				break;
									}
				
		sprintf( framestring, "%d", frame );

		if ( (frame-firstframe) % STEP == 0 )
		{		
		build_CAs( (int)(nofatoms) + 2);


		for ( i=1 ; i <= 3*nofCAs ; i++ )
			intermed[i] = 0;


		sum = cos( 2.0 * M_PI * (double)(entered) / (double)(totentered)) * 
			(EIGENPLAY_FIRST - EIGENPLAY_LAST) / 2.00 + 
			(EIGENPLAY_FIRST - EIGENPLAY_LAST) / 2.00 + EIGENPLAY_LAST;


		for ( i=0 ; i < nofCAs ; i++ )
			{
				intermed[i*3+1] = sum * eigenvectors[i*3+1][EIGENPLAY];
				intermed[i*3+2] = sum * eigenvectors[i*3+2][EIGENPLAY];
				intermed[i*3+3] = sum * eigenvectors[i*3+3][EIGENPLAY];
						}


		for ( i=0 ; i < nofCAs ; i++ )
			{
				CAs[i][0] = (float)(averCAxyz[i*3+1] + intermed[i*3+1]) ;
				CAs[i][1] = (float)(averCAxyz[i*3+2] + intermed[i*3+2]) ;
				CAs[i][2] = (float)(averCAxyz[i*3+3] + intermed[i*3+3]) ;
						}
		
		
		if ( WRITE_CAS == YES )
			{
			write_CAs2( (int)(nofCAs) + 2);
		
			if ( (unsigned int)(write( outdcd, (void *)(&wdcd_frame[1]), (size_t)(wbytes_per_set) )) != wbytes_per_set )
				{
					printf("\033[31m\033[1mFailed to write frame %d to DCD file.\033[0m\n", frame );
					myexit(1);
							}
								}
		else
			{	
			write_CAs( (int)(nofatoms) + 2);
		
			if ( (unsigned int)(write( outdcd, (void *)(&dcd_frame[1]), (size_t)(bytes_per_set) )) != bytes_per_set )
				{
					printf("\033[31m\033[1mFailed to write frame %d to DCD file.\033[0m\n", frame );
					myexit(1);
							}
								}
		
		
		entered++;

		if ( STEP > 1 )
			{
				if ( lseek( dcd, (off_t)(bytes_per_set * (off_t)(STEP-1)), SEEK_CUR ) == (off_t)(-1) )
				{
					printf("\033[31m\033[1mRequested frame not present ? Abort.\033[0m\n");
					myexit(1);
							}
				frame += (STEP-1);
			}

		}
		frame++;
		if ( VERBOSE )
		printf("%8d", frame );


						}

	if ( frame == LAST+1 && VERBOSE )
		printf("%8d\n", (frame-1) );

	
	close( outdcd );
	
#ifndef WINDOWS
	if ( VERBOSE )
		{
		end_timer = time(NULL);
		printf("\033[32m\033[1mAll done in %1.1f minutes.\033[0m\n", (float)(end_timer-start_timer)/60.0 );
		}
#endif
	
	myexit( 0 );
	

	

	}






	}
#endif






#ifndef WINDOWS	
	if ( VERBOSE )
		{
		end_timer = time(NULL);
		printf("\033[32m\033[1mAll done in %1.1f minutes.\033[0m\n", (float)(end_timer-start_timer)/60.0 );
		}
#endif

	myexit( 0 );
	}
	else
	{


/*****************************************************************************************************************************/
/**   Cross-correlation matrices	                                                                                    **/
/*****************************************************************************************************************************/

	if ( USE_DOT == YES )
	{
	D3 = matrix( 1, nofCAs, 1, nofCAs);
	pD3 = &D3[1][1];
	for ( i=1 ; i <= nofCAs ; i++ )
	for ( k=1 ; k <= nofCAs ; k++ )	
		D3[i][k] = D2[i][k] / sqrt( D2[i][i] * D2[k][k] );
	max = -1000000000000.0 ;
	min =  1000000000000.0 ; 
	for ( i=0 ; i < nofCAs*nofCAs ; i++ )
		{
			if ( pD3[i] > max )
				max =  pD3[i];
			if ( pD3[i] < min )
				min =  pD3[i];

						}
	if ( VERBOSE )
		{
			printf("Maximum of variance-covariance matrix is %f\n", max );
			printf("Minimum of variance-covariance matrix is %f\n", min );
					}			

	if ( HAVE_MIN == NO )
		gmin = min;
	if ( HAVE_MAX == NO )
		gmax = max;

	wps( D3, filename );
	}
	else
	{
	D3 = matrix( 1, 3*nofCAs, 1, 3*nofCAs);
	pD3 = &D3[1][1];
	for ( i=1 ; i <= 3*nofCAs ; i++ )
	for ( k=1 ; k <= 3*nofCAs ; k++ )	
		D3[i][k] = D2[i][k] / sqrt( D2[i][i] * D2[k][k] );
	max = -1000000000000.0 ;
	min =  1000000000000.0 ; 
	for ( i=0 ; i < 9*nofCAs*nofCAs ; i++ )
		{
			if ( pD3[i] > max )
				max =  pD3[i];
			if ( pD3[i] < min )
				min =  pD3[i];

						}
	if ( VERBOSE )
		{
			printf("Maximum of variance-covariance matrix is %f\n", max );
			printf("Minimum of variance-covariance matrix is %f\n", min );
					}			

	if ( HAVE_MIN == NO )
		gmin = min;
	if ( HAVE_MAX == NO )
		gmax = max;

	nofCAs = nofCAs * 3;
	wps( D3, filename );
	}

	myexit(0);
	}
	}


	myexit( 0 );
	return(0);
}












/*****************************************************************************************************************************/
/**   Get CA coordinates from dcd frame                                                                                     **/
/*****************************************************************************************************************************/

void	build_CAs( offset )
int	offset;
{
	int 	i;
	int	atomno;


	if ( HAVE_CELL == YES )
		{
			cell_a     = (double)(*((double *)(&dcd_frame[2] +  0)));
			cell_gamma = (double)(*((double *)(&dcd_frame[2] +  2)));
			cell_b     = (double)(*((double *)(&dcd_frame[2] +  4)));
			cell_beta  = (double)(*((double *)(&dcd_frame[2] +  6)));
			cell_alpha = (double)(*((double *)(&dcd_frame[2] +  8)));
			cell_c     = (double)(*((double *)(&dcd_frame[2] + 10)));

	if ( cell_alpha <= 1.0 && cell_beta <= 1.0 && cell_gamma <= 1.0 )
		{
			if ( cell_alpha == 0.0 )
				cell_alpha = 90.00;
			else
				cell_alpha = 180.0 * acos( cell_alpha ) / M_PI;
			if ( cell_beta == 0.0 )
				cell_beta = 90.00;
			else
				cell_beta = 180.0 * acos( cell_beta ) / M_PI;
			if ( cell_gamma == 0.0 )
				cell_gamma = 90.00;
			else
				cell_gamma = 180.0 * acos( cell_gamma ) / M_PI;
		}			

/*
	printf("%15.8f %15.8f %15.8f %15.8f %15.8f %15.8f \n", cell_a, cell_b, cell_c, cell_alpha, cell_beta, cell_gamma );
*/

		}


#ifdef GRA
	if ( GRAPHICS && !PLAYING)
	{

	if ( getbutton(XKEY) )
		GRA_VIEW = 1;
	else if ( getbutton(YKEY) )
		GRA_VIEW = 2;
	else if ( getbutton(ZKEY) )
		GRA_VIEW = 3;

	if ( getbutton(PERIODKEY) )
		{
			if ( GRABOX > 1.10 )
				GRABOX *= 0.9500;
			ortho2( -GRABOX/2.0, GRABOX/2.0, -GRABOX/2.0, GRABOX/2.0);
				}			
	if ( getbutton(COMMAKEY) )
		{
			GRABOX *= 1.0500;
			ortho2( -GRABOX/2.0, GRABOX/2.0, -GRABOX/2.0, GRABOX/2.0);
				}			

	if ( getbutton(EQUALKEY) )
		{
			STEP *=2 ;
					}
	if ( getbutton(MINUSKEY) )
		{
			STEP /= 2;
			if ( STEP < 1 )
				STEP = 1;
						}


	if ( getbutton(RIGHTARROWKEY) )
		{
			XOFFSET += GRABOX * 0.0200;
				}			
	if ( getbutton(LEFTARROWKEY) )
		{
			XOFFSET -= GRABOX * 0.0200;
				}			
	if ( getbutton(UPARROWKEY) )
		{
			YOFFSET += GRABOX * 0.0200;
				}			
	if ( getbutton(DOWNARROWKEY) )
		{
			YOFFSET -= GRABOX * 0.0200;
				}			
	if ( getbutton(RKEY) )
		{
			YOFFSET = 0.0;
			XOFFSET = 0.0;
				}			


	if ( getbutton(PKEY) )
		{	
			usleep( 200000 );
			copyCAs();
			while ( !getbutton(PKEY) )
				static_view();
			usleep( 200000 );
							}

	if ( getbutton(BKEY) && HAVE_CELL )
		{	
			usleep( 200000 );
			copyCAs();
			calc_ortho();
			PACKING = YES;
			PACKING_FIRST = YES;
			while ( !getbutton(BKEY) )
				static_view();
			PACKING = NO;
			usleep( 200000 );
							}


        for ( i=0 ; i < nofCAs ; i++ )
        {
        color(colorindex[i]);
        atomno = posCAs[i];
        CAs[i][0] = dcd_frame[ CELL_OFFSET + 2+atomno];
        CAs[i][1] = dcd_frame[ CELL_OFFSET + 2+atomno+offset];
        CAs[i][2] = dcd_frame[ CELL_OFFSET + 2+atomno+2*offset];

        if ( GRA_VIEW == 3 )
                pnt2(CAs[i][0]+XOFFSET, CAs[i][1]+YOFFSET);
        else if ( GRA_VIEW == 1 )
                pnt2(CAs[i][1]+XOFFSET, CAs[i][2]+YOFFSET);
        else
                pnt2(CAs[i][2]+XOFFSET, CAs[i][0]+YOFFSET);

        	}

        loadXfont(4711, "fixed");  
        font(4711);
        color(1);
        cmov2( -GRABOX/2.0,GRABOX/2.0-GRABOX*16.0/WINSIZE );
        charstr(framestring);



	if ( TRICK )
	{
	float	x, y, z, distance;

	if ( GRA_VIEW == 3 )
		move2(CAs[realCAs[0]][0]+XOFFSET, CAs[realCAs[0]][1]+YOFFSET);
	else if ( GRA_VIEW == 1 )
		move2(CAs[realCAs[0]][1]+XOFFSET, CAs[realCAs[0]][2]+YOFFSET);
	else
		move2(CAs[realCAs[0]][2]+XOFFSET, CAs[realCAs[0]][0]+YOFFSET);

	for ( i=1 ; i < realCAscount ; i++ )
	{
	if ( GRADIENT )
		color(colorindex[i*nofCAs/realCAscount]);
	else
		color(colorindex[realCAs[i]]);

	x = CAs[realCAs[i]][0];
	y = CAs[realCAs[i]][1];
	z = CAs[realCAs[i]][2];

	distance = sqrt( (x-CAs[realCAs[i-1]][0])*(x-CAs[realCAs[i-1]][0]) + (y-CAs[realCAs[i-1]][1])*(y-CAs[realCAs[i-1]][1])
			 + (z-CAs[realCAs[i-1]][2])*(z-CAs[realCAs[i-1]][2]) );
		
	if ( distance > limitCAs[i] )
	{
	if ( GRA_VIEW == 3 )
		move2(x+XOFFSET, y+YOFFSET);
	else if ( GRA_VIEW == 1 )
		move2(y+XOFFSET, z+YOFFSET);
	else
		move2(z+XOFFSET, x+YOFFSET);
	}
	else
	{
	if ( GRA_VIEW == 3 )
		draw2(x+XOFFSET, y+YOFFSET);
	else if ( GRA_VIEW == 1 )
		draw2(y+XOFFSET, z+YOFFSET);
	else
		draw2(z+XOFFSET, x+YOFFSET);
	}

		}
	}

	


	
	if ( DO_FIT && !CALC_MAP)
		return;


	gflush();
	swapbuffers();
	color(0);
	clear();
        color(1);
	linewidth(1);
	move2(-CROSS,0.0);
	draw2(CROSS,0.0);
	move2(0.0,-CROSS);
	draw2(0.0,CROSS);
	linewidth( LINEW );

	if ( CALC_MAP || FAST_MAP )
	{
	linewidth( 1 );
	if ( GRA_VIEW == 3 )
		{
		move2(Xmin+XOFFSET,Ymin+YOFFSET);
		draw2(Xmin+XOFFSET,Ymax+YOFFSET);		
		draw2(Xmax+XOFFSET,Ymax+YOFFSET);
		draw2(Xmax+XOFFSET,Ymin+YOFFSET);
		draw2(Xmin+XOFFSET,Ymin+YOFFSET);
		}
	else if ( GRA_VIEW == 1 )
		{
		move2(Ymin+XOFFSET,Zmin+YOFFSET);
		draw2(Ymin+XOFFSET,Zmax+YOFFSET);		
		draw2(Ymax+XOFFSET,Zmax+YOFFSET);
		draw2(Ymax+XOFFSET,Zmin+YOFFSET);
		draw2(Ymin+XOFFSET,Zmin+YOFFSET);
		}
	else
		{
		move2(Zmin+XOFFSET,Xmin+YOFFSET);
		draw2(Zmin+XOFFSET,Xmax+YOFFSET);		
		draw2(Zmax+XOFFSET,Xmax+YOFFSET);
		draw2(Zmax+XOFFSET,Xmin+YOFFSET);
		draw2(Zmin+XOFFSET,Xmin+YOFFSET);
		}
	linewidth( LINEW );
	}


        color(255);
	linewidth( 1 );
	for ( i=0 ; i < GRABOX/2.0 ; i += 5)
		{
			move2(i, -GRABOX/2.0);
			draw2(i, -GRABOX/2.0+CROSS);
			move2(i, GRABOX/2.0);
			draw2(i, GRABOX/2.0-CROSS);
				}
	for ( i=-5 ; i > -GRABOX/2.0 ; i -= 5)
		{
			move2(i, -GRABOX/2.0);
			draw2(i, -GRABOX/2.0+CROSS);
			move2(i, GRABOX/2.0);
			draw2(i, GRABOX/2.0-CROSS);
				}
	for ( i=0 ; i < GRABOX/2.0 ; i += 5)
		{
			move2(-GRABOX/2.0,i);
			draw2(-GRABOX/2.0+CROSS,i);
			move2(GRABOX/2.0,i);
			draw2(GRABOX/2.0-CROSS,i);
				}
	for ( i=-5 ; i > -GRABOX/2.0 ; i -= 5)
		{
			move2(-GRABOX/2.0,i);
			draw2(-GRABOX/2.0+CROSS,i);
			move2(GRABOX/2.0,i);
			draw2(GRABOX/2.0-CROSS,i);
				}

	linewidth( LINEW );
	return;
	}
#endif

	for ( i=0 ; i < nofCAs ; i++ )
	{
	atomno = posCAs[i];
	CAs[i][0] = dcd_frame[ CELL_OFFSET + 2+atomno];
	CAs[i][1] = dcd_frame[ CELL_OFFSET + 2+atomno+offset];
	CAs[i][2] = dcd_frame[ CELL_OFFSET + 2+atomno+2*offset];
	}



	return;

	
}



/*****************************************************************************************************************************/
/**   Put them back in ...	 	                                                                                    **/
/*****************************************************************************************************************************/

void	write_CAs( offset )
int	offset;
{
	int 	i;
	int	atomno;



	if ( HAVE_CELL == YES )
		{
			*((double *)(&dcd_frame[2] +  0)) = cell_a;
			*((double *)(&dcd_frame[2] +  2)) = cell_gamma;
			*((double *)(&dcd_frame[2] +  4)) = cell_b;
			*((double *)(&dcd_frame[2] +  6)) = cell_beta;
			*((double *)(&dcd_frame[2] +  8)) = cell_alpha;
			*((double *)(&dcd_frame[2] + 10)) = cell_c;
		}

#ifdef GRA
	if ( GRAPHICS )
	{

	if ( getbutton(XKEY) )
		GRA_VIEW = 1;
	else if ( getbutton(YKEY) )
		GRA_VIEW = 2;
	else if ( getbutton(ZKEY) )
		GRA_VIEW = 3;

	if ( getbutton(PERIODKEY) )
		{
			if ( GRABOX > 1.10 )
				GRABOX *= 0.9500;
			ortho2( -GRABOX/2.0, GRABOX/2.0, -GRABOX/2.0, GRABOX/2.0);
				}			
	if ( getbutton(COMMAKEY) )
		{
			GRABOX *= 1.0500;
			ortho2( -GRABOX/2.0, GRABOX/2.0, -GRABOX/2.0, GRABOX/2.0);
				}			
        if ( getbutton(EQUALKEY) )
                {
                        STEP *= 2;
                                        }
        if ( getbutton(MINUSKEY) )
                {              
                        STEP /= 2;
                        if ( STEP < 1 )
                                STEP = 1;
                                                }

	if ( getbutton(RIGHTARROWKEY) )
		{
			XOFFSET += GRABOX * 0.0200;
				}			
	if ( getbutton(LEFTARROWKEY) )
		{
			XOFFSET -= GRABOX * 0.0200;
				}			
	if ( getbutton(UPARROWKEY) )
		{
			YOFFSET += GRABOX * 0.0200;
				}			
	if ( getbutton(DOWNARROWKEY) )
		{
			YOFFSET -= GRABOX * 0.0200;
				}			
	if ( getbutton(RKEY) )
		{
			YOFFSET = 0.0;
			XOFFSET = 0.0;
				}			

	if ( getbutton(PKEY) )
		{	
			usleep( 200000 );
			copyCAs();
			while ( !getbutton(PKEY) )
				static_view();
			usleep( 200000 );
							}

	if ( getbutton(BKEY) && HAVE_CELL )
		{	
			usleep( 200000 );
			copyCAs();
			calc_ortho();
			PACKING = YES;
			PACKING_FIRST = YES;
			while ( !getbutton(BKEY) )
				static_view();
			PACKING = NO;
			usleep( 200000 );
							}


	if ( DO_FIT )
	{
	color(255);


	for ( i=0 ; i < nofCAs ; i++ )
	{
	atomno = posCAs[i];
	dcd_frame[ CELL_OFFSET + 2+atomno] = CAs[i][0];
	dcd_frame[ CELL_OFFSET + 2+atomno+offset] = CAs[i][1];
	dcd_frame[ CELL_OFFSET + 2+atomno+2*offset] = CAs[i][2];

	if ( GRA_VIEW == 3 )
		pnt2(CAs[i][0]+XOFFSET, CAs[i][1]+YOFFSET);
	else if ( GRA_VIEW == 1 )
		pnt2(CAs[i][1]+XOFFSET, CAs[i][2]+YOFFSET);
	else
		pnt2(CAs[i][2]+XOFFSET, CAs[i][0]+YOFFSET);

	}


	
	if ( TRICK )
	{
	float	x, y, z, distance;

	if ( GRA_VIEW == 3 )
		move2(CAs[realCAs[0]][0]+XOFFSET, CAs[realCAs[0]][1]+YOFFSET);
	else if ( GRA_VIEW == 1 )
		move2(CAs[realCAs[0]][1]+XOFFSET, CAs[realCAs[0]][2]+YOFFSET);
	else
		move2(CAs[realCAs[0]][2]+XOFFSET, CAs[realCAs[0]][0]+YOFFSET);

	for ( i=1 ; i < realCAscount ; i++ )
	{

	x = CAs[realCAs[i]][0];
	y = CAs[realCAs[i]][1];
	z = CAs[realCAs[i]][2];

	distance = sqrt( (x-CAs[realCAs[i-1]][0])*(x-CAs[realCAs[i-1]][0]) + (y-CAs[realCAs[i-1]][1])*(y-CAs[realCAs[i-1]][1])
			 + (z-CAs[realCAs[i-1]][2])*(z-CAs[realCAs[i-1]][2]) );
	
	if ( distance > limitCAs[i] )
	{
	if ( GRA_VIEW == 3 )
		move2(x+XOFFSET, y+YOFFSET);
	else if ( GRA_VIEW == 1 )
		move2(y+XOFFSET, z+YOFFSET);
	else
		move2(z+XOFFSET, x+YOFFSET);
	}
	else
	{
	if ( GRA_VIEW == 3 )
		draw2(x+XOFFSET, y+YOFFSET);
	else if ( GRA_VIEW == 1 )
		draw2(y+XOFFSET, z+YOFFSET);
	else
		draw2(z+XOFFSET, x+YOFFSET);
	}

		}
	}





	gflush();
	swapbuffers();
	color(0);
	clear();
        color(1);
	move2(-CROSS,0.0);
	draw2(CROSS,0.0);
	move2(0.0,-CROSS);
	draw2(0.0,CROSS);
        color(255);
	linewidth( 1 );
	for ( i=0 ; i < GRABOX/2.0 ; i += 5)
		{
			move2(i, -GRABOX/2.0);
			draw2(i, -GRABOX/2.0+CROSS);
			move2(i, GRABOX/2.0);
			draw2(i, GRABOX/2.0-CROSS);
				}
	for ( i=-5 ; i > -GRABOX/2.0 ; i -= 5)
		{
			move2(i, -GRABOX/2.0);
			draw2(i, -GRABOX/2.0+CROSS);
			move2(i, GRABOX/2.0);
			draw2(i, GRABOX/2.0-CROSS);
				}
	for ( i=0 ; i < GRABOX/2.0 ; i += 5)
		{
			move2(-GRABOX/2.0,i);
			draw2(-GRABOX/2.0+CROSS,i);
			move2(GRABOX/2.0,i);
			draw2(GRABOX/2.0-CROSS,i);
				}
	for ( i=-5 ; i > -GRABOX/2.0 ; i -= 5)
		{
			move2(-GRABOX/2.0,i);
			draw2(-GRABOX/2.0+CROSS,i);
			move2(GRABOX/2.0,i);
			draw2(GRABOX/2.0-CROSS,i);
				}
	linewidth( LINEW );

	return;
	}
	else
	{


	for ( i=0 ; i < nofCAs ; i++ )
	{
	color(colorindex[i]);

	atomno = posCAs[i];
	dcd_frame[ CELL_OFFSET + 2+atomno] = CAs[i][0];
	dcd_frame[ CELL_OFFSET + 2+atomno+offset] = CAs[i][1];
	dcd_frame[ CELL_OFFSET + 2+atomno+2*offset] = CAs[i][2];

	if ( GRA_VIEW == 3 )
		pnt2(CAs[i][0]+XOFFSET, CAs[i][1]+YOFFSET);
	else if ( GRA_VIEW == 1 )
		pnt2(CAs[i][1]+XOFFSET, CAs[i][2]+YOFFSET);
	else
		pnt2(CAs[i][2]+XOFFSET, CAs[i][0]+YOFFSET);

	}

	if ( TRICK )
	{
	float	x, y, z, distance;

	if ( GRA_VIEW == 3 )
		move2(CAs[realCAs[0]][0]+XOFFSET, CAs[realCAs[0]][1]+YOFFSET);
	else if ( GRA_VIEW == 1 )
		move2(CAs[realCAs[0]][1]+XOFFSET, CAs[realCAs[0]][2]+YOFFSET);
	else
		move2(CAs[realCAs[0]][2]+XOFFSET, CAs[realCAs[0]][0]+YOFFSET);

	for ( i=1 ; i < realCAscount ; i++ )
	{
	color(colorindex[i]);

	x = CAs[realCAs[i]][0];
	y = CAs[realCAs[i]][1];
	z = CAs[realCAs[i]][2];

	distance = sqrt( (x-CAs[realCAs[i-1]][0])*(x-CAs[realCAs[i-1]][0]) + (y-CAs[realCAs[i-1]][1])*(y-CAs[realCAs[i-1]][1])
			 + (z-CAs[realCAs[i-1]][2])*(z-CAs[realCAs[i-1]][2]) );
	
	if ( distance > limitCAs[i] )
	{
	if ( GRA_VIEW == 3 )
		move2(x+XOFFSET, y+YOFFSET);
	else if ( GRA_VIEW == 1 )
		move2(y+XOFFSET, z+YOFFSET);
	else
		move2(z+XOFFSET, x+YOFFSET);
	}
	else
	{
	if ( GRA_VIEW == 3 )
		draw2(x+XOFFSET, y+YOFFSET);
	else if ( GRA_VIEW == 1 )
		draw2(y+XOFFSET, z+YOFFSET);
	else
		draw2(z+XOFFSET, x+YOFFSET);
	}

		}
	}




	gflush();
	swapbuffers();
	color(0);
	clear();
        color(1);
	move2(-CROSS,0.0);
	draw2(CROSS,0.0);
	move2(0.0,-CROSS);
	draw2(0.0,CROSS);
        color(255);
	linewidth( 1 );
	for ( i=0 ; i < GRABOX/2.0 ; i += 5)
		{
			move2(i, -GRABOX/2.0);
			draw2(i, -GRABOX/2.0+CROSS);
			move2(i, GRABOX/2.0);
			draw2(i, GRABOX/2.0-CROSS);
				}
	for ( i=-5 ; i > -GRABOX/2.0 ; i -= 5)
		{
			move2(i, -GRABOX/2.0);
			draw2(i, -GRABOX/2.0+CROSS);
			move2(i, GRABOX/2.0);
			draw2(i, GRABOX/2.0-CROSS);
				}
	for ( i=0 ; i < GRABOX/2.0 ; i += 5)
		{
			move2(-GRABOX/2.0,i);
			draw2(-GRABOX/2.0+CROSS,i);
			move2(GRABOX/2.0,i);
			draw2(GRABOX/2.0-CROSS,i);
				}
	for ( i=-5 ; i > -GRABOX/2.0 ; i -= 5)
		{
			move2(-GRABOX/2.0,i);
			draw2(-GRABOX/2.0+CROSS,i);
			move2(GRABOX/2.0,i);
			draw2(GRABOX/2.0-CROSS,i);
				}
	linewidth( LINEW );

	return;
	}
	}
#endif


	for ( i=0 ; i < nofCAs ; i++ )
	{
	atomno = posCAs[i];
	dcd_frame[ CELL_OFFSET + 2+atomno] = CAs[i][0];
	dcd_frame[ CELL_OFFSET + 2+atomno+offset] = CAs[i][1];
	dcd_frame[ CELL_OFFSET + 2+atomno+2*offset] = CAs[i][2];
	}

	return;
	
}





void	write_CAs2( offset )
int	offset;
{
	int 	i;


	if ( HAVE_CELL == YES )
		{
			*((double *)(&wdcd_frame[2] +  0)) = cell_a;
			*((double *)(&wdcd_frame[2] +  2)) = cell_gamma;
			*((double *)(&wdcd_frame[2] +  4)) = cell_b;
			*((double *)(&wdcd_frame[2] +  6)) = cell_beta;
			*((double *)(&wdcd_frame[2] +  8)) = cell_alpha;
			*((double *)(&wdcd_frame[2] + 10)) = cell_c;
		}

#ifdef GRA
	if ( GRAPHICS )
	{

	if ( getbutton(XKEY) )
		GRA_VIEW = 1;
	else if ( getbutton(YKEY) )
		GRA_VIEW = 2;
	else if ( getbutton(ZKEY) )
		GRA_VIEW = 3;

	if ( getbutton(PERIODKEY) )
		{
			if ( GRABOX > 1.10 )
				GRABOX *= 0.9500;
			ortho2( -GRABOX/2.0, GRABOX/2.0, -GRABOX/2.0, GRABOX/2.0);
				}			
	if ( getbutton(COMMAKEY) )
		{
			GRABOX *= 1.0500;
			ortho2( -GRABOX/2.0, GRABOX/2.0, -GRABOX/2.0, GRABOX/2.0);
				}			
        if ( getbutton(EQUALKEY) )
                {
                        STEP *= 2;
                                        }
        if ( getbutton(MINUSKEY) )
                {              
                        STEP /= 2;
                        if ( STEP < 1 )
                                STEP = 1;
                                                }

	if ( getbutton(RIGHTARROWKEY) )
		{
			XOFFSET += GRABOX * 0.0200;
				}			
	if ( getbutton(LEFTARROWKEY) )
		{
			XOFFSET -= GRABOX * 0.0200;
				}			
	if ( getbutton(UPARROWKEY) )
		{
			YOFFSET += GRABOX * 0.0200;
				}			
	if ( getbutton(DOWNARROWKEY) )
		{
			YOFFSET -= GRABOX * 0.0200;
				}			
	if ( getbutton(RKEY) )
		{
			YOFFSET = 0.0;
			XOFFSET = 0.0;
				}			

	if ( getbutton(PKEY) )
		{	
			usleep( 200000 );
			copyCAs();
			while ( !getbutton(PKEY) )
				static_view();
			usleep( 200000 );
							}

	if ( getbutton(BKEY) && HAVE_CELL )
		{	
			usleep( 200000 );
			copyCAs();
			calc_ortho();
			PACKING = YES;
			PACKING_FIRST = YES;
			while ( !getbutton(BKEY) )
				static_view();
			PACKING = NO;
			usleep( 200000 );
							}



	if ( DO_FIT )
	{
	color(255);


	for ( i=0 ; i < nofCAs ; i++ )
	{

	wdcd_frame[ CELL_OFFSET + 2+i] = CAs[i][0];
	wdcd_frame[ CELL_OFFSET + 2+i+offset] = CAs[i][1];
	wdcd_frame[ CELL_OFFSET + 2+i+2*offset] = CAs[i][2];

	if ( GRA_VIEW == 3 )
		pnt2(CAs[i][0]+XOFFSET, CAs[i][1]+YOFFSET);
	else if ( GRA_VIEW == 1 )
		pnt2(CAs[i][1]+XOFFSET, CAs[i][2]+YOFFSET);
	else
		pnt2(CAs[i][2]+XOFFSET, CAs[i][0]+YOFFSET);

	}


	if ( TRICK )
	{
	float	x, y, z, distance;

	if ( GRA_VIEW == 3 )
		move2(CAs[realCAs[0]][0]+XOFFSET, CAs[realCAs[0]][1]+YOFFSET);
	else if ( GRA_VIEW == 1 )
		move2(CAs[realCAs[0]][1]+XOFFSET, CAs[realCAs[0]][2]+YOFFSET);
	else
		move2(CAs[realCAs[0]][2]+XOFFSET, CAs[realCAs[0]][0]+YOFFSET);

	for ( i=1 ; i < realCAscount ; i++ )
	{

	x = CAs[realCAs[i]][0];
	y = CAs[realCAs[i]][1];
	z = CAs[realCAs[i]][2];

	distance = sqrt( (x-CAs[realCAs[i-1]][0])*(x-CAs[realCAs[i-1]][0]) + (y-CAs[realCAs[i-1]][1])*(y-CAs[realCAs[i-1]][1])
			 + (z-CAs[realCAs[i-1]][2])*(z-CAs[realCAs[i-1]][2]) );
	
	if ( distance > limitCAs[i] )
	{
	if ( GRA_VIEW == 3 )
		move2(x+XOFFSET, y+YOFFSET);
	else if ( GRA_VIEW == 1 )
		move2(y+XOFFSET, z+YOFFSET);
	else
		move2(z+XOFFSET, x+YOFFSET);
	}
	else
	{
	if ( GRA_VIEW == 3 )
		draw2(x+XOFFSET, y+YOFFSET);
	else if ( GRA_VIEW == 1 )
		draw2(y+XOFFSET, z+YOFFSET);
	else
		draw2(z+XOFFSET, x+YOFFSET);
	}

		}
	}





	gflush();
	swapbuffers();
	color(0);
	clear();
        color(1);
	move2(-CROSS,0.0);
	draw2(CROSS,0.0);
	move2(0.0,-CROSS);
	draw2(0.0,CROSS);
        color(255);
	linewidth( 1 );
	for ( i=0 ; i < GRABOX/2.0 ; i += 5)
		{
			move2(i, -GRABOX/2.0);
			draw2(i, -GRABOX/2.0+CROSS);
			move2(i, GRABOX/2.0);
			draw2(i, GRABOX/2.0-CROSS);
				}
	for ( i=-5 ; i > -GRABOX/2.0 ; i -= 5)
		{
			move2(i, -GRABOX/2.0);
			draw2(i, -GRABOX/2.0+CROSS);
			move2(i, GRABOX/2.0);
			draw2(i, GRABOX/2.0-CROSS);
				}
	for ( i=0 ; i < GRABOX/2.0 ; i += 5)
		{
			move2(-GRABOX/2.0,i);
			draw2(-GRABOX/2.0+CROSS,i);
			move2(GRABOX/2.0,i);
			draw2(GRABOX/2.0-CROSS,i);
				}
	for ( i=-5 ; i > -GRABOX/2.0 ; i -= 5)
		{
			move2(-GRABOX/2.0,i);
			draw2(-GRABOX/2.0+CROSS,i);
			move2(GRABOX/2.0,i);
			draw2(GRABOX/2.0-CROSS,i);
				}

	linewidth( LINEW );
	return;
	}
	else
	{

	for ( i=0 ; i < nofCAs ; i++ )
	{
	color(colorindex[i]);
	wdcd_frame[ CELL_OFFSET + 2+i] = CAs[i][0];
	wdcd_frame[ CELL_OFFSET + 2+i+offset] = CAs[i][1];
	wdcd_frame[ CELL_OFFSET + 2+i+2*offset] = CAs[i][2];

	if ( GRA_VIEW == 3 )
		pnt2(CAs[i][0]+XOFFSET, CAs[i][1]+YOFFSET);
	else if ( GRA_VIEW == 1 )
		pnt2(CAs[i][1]+XOFFSET, CAs[i][2]+YOFFSET);
	else
		pnt2(CAs[i][2]+XOFFSET, CAs[i][0]+YOFFSET);

	}

	if ( TRICK )
	{
	float	x, y, z, distance;

	if ( GRA_VIEW == 3 )
		move2(CAs[realCAs[0]][0]+XOFFSET, CAs[realCAs[0]][1]+YOFFSET);
	else if ( GRA_VIEW == 1 )
		move2(CAs[realCAs[0]][1]+XOFFSET, CAs[realCAs[0]][2]+YOFFSET);
	else
		move2(CAs[realCAs[0]][2]+XOFFSET, CAs[realCAs[0]][0]+YOFFSET);

	for ( i=1 ; i < realCAscount ; i++ )
	{

	color(colorindex[i]);

	x = CAs[realCAs[i]][0];
	y = CAs[realCAs[i]][1];
	z = CAs[realCAs[i]][2];

	distance = sqrt( (x-CAs[realCAs[i-1]][0])*(x-CAs[realCAs[i-1]][0]) + (y-CAs[realCAs[i-1]][1])*(y-CAs[realCAs[i-1]][1])
			 + (z-CAs[realCAs[i-1]][2])*(z-CAs[realCAs[i-1]][2]) );
	
	if ( distance > limitCAs[i] )
	{
	if ( GRA_VIEW == 3 )
		move2(x+XOFFSET, y+YOFFSET);
	else if ( GRA_VIEW == 1 )
		move2(y+XOFFSET, z+YOFFSET);
	else
		move2(z+XOFFSET, x+YOFFSET);
	}
	else
	{
	if ( GRA_VIEW == 3 )
		draw2(x+XOFFSET, y+YOFFSET);
	else if ( GRA_VIEW == 1 )
		draw2(y+XOFFSET, z+YOFFSET);
	else
		draw2(z+XOFFSET, x+YOFFSET);
	}

		}
	}





	gflush();
	swapbuffers();
	color(0);
	clear();
        color(1);
	move2(-CROSS,0.0);
	draw2(CROSS,0.0);
	move2(0.0,-CROSS);
	draw2(0.0,CROSS);
        color(255);
	linewidth( 1 );
	for ( i=0 ; i < GRABOX/2.0 ; i += 5)
		{
			move2(i, -GRABOX/2.0);
			draw2(i, -GRABOX/2.0+CROSS);
			move2(i, GRABOX/2.0);
			draw2(i, GRABOX/2.0-CROSS);
				}
	for ( i=-5 ; i > -GRABOX/2.0 ; i -= 5)
		{
			move2(i, -GRABOX/2.0);
			draw2(i, -GRABOX/2.0+CROSS);
			move2(i, GRABOX/2.0);
			draw2(i, GRABOX/2.0-CROSS);
				}
	for ( i=0 ; i < GRABOX/2.0 ; i += 5)
		{
			move2(-GRABOX/2.0,i);
			draw2(-GRABOX/2.0+CROSS,i);
			move2(GRABOX/2.0,i);
			draw2(GRABOX/2.0-CROSS,i);
				}
	for ( i=-5 ; i > -GRABOX/2.0 ; i -= 5)
		{
			move2(-GRABOX/2.0,i);
			draw2(-GRABOX/2.0+CROSS,i);
			move2(GRABOX/2.0,i);
			draw2(GRABOX/2.0-CROSS,i);
				}
	linewidth( LINEW );

	return;
	}
	}
#endif

	for ( i=0 ; i < nofCAs ; i++ )
	{
	wdcd_frame[ CELL_OFFSET + 2+i] = CAs[i][0];
	wdcd_frame[ CELL_OFFSET + 2+i+offset] = CAs[i][1];
	wdcd_frame[ CELL_OFFSET + 2+i+2*offset] = CAs[i][2];
	}

	
	return;
	
}




/*****************************************************************************************************************************/
/**   Calculate distance matrix                                                                                             **/
/*****************************************************************************************************************************/

float	Dist()
{
	float	max;
	int	i, k;
	float	x,y,z;
	float	dx, dy,dz;
	float	d;
	
	max = 0.0;
 	for ( i=1 ; i <= nofCAs ; i++ )
	{
	x = CAs[i-1][0];
	y = CAs[i-1][1];
	z = CAs[i-1][2];

	for ( k=i ; k <= nofCAs ; k++ )
	{	
		dx = x - CAs[k-1][0];
		dy = y - CAs[k-1][1];
		dz = z - CAs[k-1][2];
		d = sqrt( dx*dx + dy*dy + dz*dz ); 
		D1[i][k] = d;
		D1[k][i] = d;
		max = max2( max, d );
		
		if ( PDDF == YES )
			pddf[ (int)(d / PDDF_STEP) ] += masses[i-1] * masses[k-1] * d * d;
		
	}
	}

	return( max );
}




/*****************************************************************************************************************************/
/**   Get what we need from the .psf file                                                                                   **/
/*****************************************************************************************************************************/

int 	read_psf( name )
char 	name[];
{
	FILE 	*in;
	char	string[300];	
	int	nof = 0;	
	int	nof2 = 0;
	int	i;
        int	nseg;
        int	natm;
        int	k;
        int	lines;
        int	INDEX_1  = 23;
        int	INDEX_11 = 24;
        int	INDEX_2  =  9;
        int	INDEX_22 =  8;
        int	INDEX_3  = 14;
        int	INDEX_4  = 19;
        int	INDEX_5  = 29;
        int	INDEX_6  = 50;
	int	EXTENDED = NO;        
	int	UNKNOWN = NO;
	FILE	*out = 0;
	int	ZERO_MASSES = NO;	
        
        
	in = fopen( name, "r" );
	if ( in == NULL )
		{
			printf("\033[31m\033[1mCan not open .psf file for read. Abort.\n");
			myexit( 1 );
					}

	if ( WRITE_DATA == YES )
	{
	out = fopen( "carma.selected_atoms.psf", "w+" );
	if ( out == NULL )
		{
			printf("\033[31m\033[1mCan not open file for writing selected atoms. Abort.\n");
			myexit( 1 );
					}
	}
	
	
	if ( fgets( string, 299, in ) != NULL )
		{
			int	items;
			char	strings[6][10];

			if ( WRITE_DATA == YES )
				fprintf(out, "%s", string );
						
			items = sscanf( string, "%s %s %s %s %s %s", &strings[0][0],&strings[1][0],&strings[2][0],
					   			     &strings[3][0],&strings[4][0],&strings[5][0] );

			if ( 	strncasecmp( &strings[1][0], "EXT", 3) == 0 ||
				strncasecmp( &strings[2][0], "EXT", 3) == 0 ||
				strncasecmp( &strings[3][0], "EXT", 3) == 0 ||
				strncasecmp( &strings[4][0], "EXT", 3) == 0 ||
				strncasecmp( &strings[5][0], "EXT", 3) == 0 )
				{
				if ( VERBOSE )
				printf("\033[32m\033[1mPSF with the EXT extension detected.\033[0m\n");

				EXTENDED = YES;
				INDEX_1  = 37;
				INDEX_11 = 38;
				INDEX_2  = 11;
				INDEX_22 = 10;
				INDEX_3  = 20;
				INDEX_4  = 29;
				INDEX_5  = 47;
				INDEX_6  = 68;

				}		
		}
	else
		{
			printf("\033[31m\033[1mEmpty PSF file ? Abort.\033[0m\n");
			myexit( 1 );
		}


        while ( fgets( string, 299, in ) != NULL )                              /* Find number of atoms */
		if ( strstr( string, "!NATOM") != NULL )				
			{
				nof = atoi( string );
				break;
					}
		else
			{
				if ( WRITE_DATA == YES )
					fprintf(out, "%s", string );
			}
	
	if ( WRITE_DATA == YES )		
		fprintf(out, "%s", string );
			
	if ( nof == 0 )
		{
			printf("\033[31m\033[1mPSF file without an NATOM card ? Abort.\033[0m\n");
			myexit( 1 );
					}
	
	for ( i=0 ; i < nof ; i++ )
		{
		if ( fgets( string, 299, in ) == NULL )
			{
				printf("\033[31m\033[1mCorrupt .psf file ? Abort.\033[0m\n");
				myexit( 1 );
						}
		
		if ( strlen( string ) < 2 )
			{
				printf("\033[31m\033[1mEmpty line in .psf file while reading atom lines ? Abort.\033[0m\n");
				myexit( 1 );			
			}
		
		if ( HAVE_SEGID == NO )
		{
		for ( natm = 0 ; natm < strlen( ATOMID) / 5 ; natm++ )
		if ( strncasecmp( &string[INDEX_1], &ATOMID[natm*5], 5) == 0 || ALL_ATID == YES || (HEAVY==YES && strncasecmp( &string[INDEX_11], "H", 1) != 0) )
			{

			strncpy( &str_segname[nof2][0], &string[INDEX_2],  4 );
			str_resid[nof2] = atoi( &string[INDEX_3] );
			strncpy( &str_resname[nof2][0], &string[INDEX_4], 4 );
			strncpy( &str_atname[nof2][0],  &string[INDEX_11], 4 );
			str_segname[nof2][1] = 0;
			str_resname[nof2][3] = 0;
			str_atname[nof2][3] = 0;
			
			if ( WRITE_DATA == YES )
				fprintf(out, "%s", string );


#ifdef GRA
			if ( TRICK && TRICK_FIRST < 0 && (strncasecmp( &string[INDEX_1], " CA  ", 5) == 0 || strncasecmp( &string[INDEX_1], " P   ", 5) == 0))
				TRICK_FIRST = nof2;

			if ( TRICK && (strncasecmp( &string[INDEX_1], " CA  ", 5) == 0 || strncasecmp( &string[INDEX_1], " P   ", 5) == 0))
				{
					if ( strncasecmp( &string[INDEX_1], " CA  ", 5) == 0 )
						limitCAs[realCAscount] = 5;
					else
						limitCAs[realCAscount] = 8;

					realCAs[realCAscount++] = nof2;
					TRICK_LAST = nof2;
				}
#endif

			for ( k=0 ; k < ATOM_TYPES ; k++ )
				if ( strncasecmp( &string[INDEX_5], atom_names[k], 4) == 0 )
					{
						masses[nof2] = atom_masses[k];
#ifdef GRA
						if ( GRAPHICS && CPK )
							colorindex[nof2] = atom_colors[k];
#endif
						break;
								}

			if ( k == ATOM_TYPES )
				{
					if ( !EXTENDED )
						UNKNOWN = YES;
						
					/* printf("\033[31mUnknown atom type in the following PSF line :\n  %s\033[0m", string); */

					masses[nof2] = atof( &string[INDEX_6] );

					/* if ( !EXTENDED )
					printf("\033[31mGot a value of %f from the PSF file.\033[0m\n\n", masses[nof2] ); */

#ifdef GRA
						if ( GRAPHICS && CPK )
							colorindex[nof2] = OTHERC;
#endif

							}

			if ( masses[nof2] < 0.5 )
				ZERO_MASSES = YES;


#ifdef GRA
			if ( GRAPHICS && !CPK)
				colorindex[nof2] = natm + 2;
#endif

			posCAs[nof2] = i;
			nof2++;
			if ( nof2 == MAX_NOF_CAS - 1 )
				{
					printf("\033[31mMaximum number of atoms exceeded. Change MAX_NOF_CAS and re-compile.\033[0m\n");
					myexit(1);
							}
								}
									}
		else
		{
		for ( natm = 0 ; natm < strlen( ATOMID) / 5 ; natm++ )
		for ( nseg = 0 ; nseg < strlen( SEGID) / 5 ; nseg++ )
		if ( strncasecmp( &string[INDEX_22], &SEGID[nseg*5], 5) == 0 && (strncasecmp( &string[INDEX_1], &ATOMID[natm*5], 5) == 0 || ALL_ATID == YES || (HEAVY==YES && strncasecmp( &string[INDEX_11], "H", 1) != 0)))
			{

			strncpy( &str_segname[nof2][0], &string[INDEX_2],  4 );
			str_resid[nof2] = atoi( &string[INDEX_3] );
			strncpy( &str_resname[nof2][0], &string[INDEX_4], 4 );
			strncpy( &str_atname[nof2][0],  &string[INDEX_11], 4 );
			str_segname[nof2][1] = 0;
			str_resname[nof2][3] = 0;
			str_atname[nof2][3] = 0;

			if ( WRITE_DATA == YES )
				fprintf(out, "%s", string );

			if ( DPCA == YES )
			{
			strncpy( &backbone[nof2][0], &SEGID[nseg*5], 5 );
			strncpy( &backbone[nof2][5], &ATOMID[natm*5], 5 );
			backbone[nof2][10] = 0;
			if ( nof2 == MAX_NOF_BACK - 2 )
				{
					printf("\033[31mMaximum number of backbone atoms exceeded. Change MAX_NOF_BACK and re-compile.\033[0m\n");
					myexit(1);
							}

	
			}
#ifdef GRA
			if ( TRICK && TRICK_FIRST < 0 && (strncasecmp( &string[INDEX_1], " CA  ", 5) == 0 || strncasecmp( &string[INDEX_1], " P   ", 5) == 0))
				TRICK_FIRST = nof2;

			if ( TRICK && (strncasecmp( &string[INDEX_1], " CA  ", 5) == 0 || strncasecmp( &string[INDEX_1], " P   ", 5) == 0))
				{
					if ( strncasecmp( &string[INDEX_1], " CA  ", 5) == 0 )
						limitCAs[realCAscount] = 5;
					else
						limitCAs[realCAscount] = 8;

					realCAs[realCAscount++] = nof2;
					TRICK_LAST = nof2;
				}
#endif

			for ( k=0 ; k < ATOM_TYPES ; k++ )
				if ( strncasecmp( &string[INDEX_5], atom_names[k], 4) == 0 )
					{
						masses[nof2] = atom_masses[k];
#ifdef GRA
						if ( GRAPHICS && CPK )
							colorindex[nof2] = atom_colors[k];
#endif
						break;
								}

			if ( k == ATOM_TYPES )
				{

                                        if ( !EXTENDED )
                                        	UNKNOWN = YES;
                                                
                                        /* printf("\033[31mUnknown atom type in the following PSF line :\n  %s\033[0m", string); */
                                     
                                        masses[nof2] = atof( &string[INDEX_6] );                                           
                                                                                                                              
                                        /* if ( !EXTENDED )
                                        printf("\033[31mGot a value of %f from the PSF file.\033[0m\n\n", masses[nof2] ); */

							}


			if ( masses[nof2] < 0.5 )
				ZERO_MASSES = YES;


#ifdef GRA
			if ( GRAPHICS && !CPK)
				colorindex[nof2] = nseg+2;
#endif

			posCAs[nof2] = i;
			nof2++;
			if ( nof2 == MAX_NOF_CAS - 1 )
				{
					printf("\033[31mMaximum number of atoms exceeded. Change MAX_NOF_CAS and re-compile.\033[0m\n");
					myexit(1);
							}
								}
									}
				
					
					}
#ifdef GRA
	if ( GRAPHICS && GRADIENT && !CPK )
		for ( i=0 ; i < nof2 ; i++ )
			colorindex[i] = (int)((254*i)/nof2) > 1 ? (int)((254*i)/nof2) : 2;
#endif


	if ( WRITE_DATA == YES )
	{	
	rewind( out );

	lines = 0;
        while ( fgets( string, 299, out ) != NULL )                              /* Update number of atoms */
		if ( strstr( string, "!NATOM") != NULL )				
			break;
		else
			lines++;
	
	rewind( out );
	for ( i=0 ; i < lines ; i++ )
		fgets( string, 299, out );
	
	fprintf( out, " % 7d !NATOM", nof2);
	

	fclose( out );
	}
	
	
	fclose( in );	
	
	nofPSFatoms = nof;

/*
	if ( VERBOSE && UNKNOWN )
		printf("\033[31mUnknown atom types detected in the PSF. Continuing.\n\033[0m");
*/

	if ( ZERO_MASSES == YES )
		printf("\033[33mSome atoms' masses were zero. TIP4P maybe ???\n\033[0m");
	


	return( nof2 );



}







/*****************************************************************************************************************************/
/**   Write postscript file of the data in **data, using a linear grayscale between gmin and gmax                           **/
/*****************************************************************************************************************************/

void 	wps( data, name )
float	**data;
char	name[];
{
	FILE	*out;
	char 	newname[300];
	int	i, k;
	int	line_indicator = 0;
	int	gray;
	float	scale;	
	float	val;


	if ( COLOUR == YES )
		{
			wps_color( data, name );
			return;
		}


        if ( SIGMOIDAL == YES )
        {
	if ( VERBOSE )
		printf("Values will be weighted with a sigmoidal function (l=%f).\n", LAMBDA );
	for ( i=1 ; i <= nofCAs ; i++)
	for ( k=1 ; k <= nofCAs ; k++)
		data[i][k] = ((2.0 / (1.0+exp(-LAMBDA*data[i][k]))) - 1.0);	
	}


	if ( WRITE_DATA == YES )
	{
	strcpy( newname, name );
	strcat( newname, ".dat");
	out = fopen( newname, "w" );
        if ( out == NULL )
                {
                printf("\033[31m\033[1mCan not open data file for writing. Abort.\n");
                myexit(1);
                }
	if ( VERBOSE )
		printf("Writing data (formatted ASCII) to the file %s.\n", newname );

	for ( i=1 ; i <= nofCAs ; i++)
	{
	for ( k=1 ; k <= nofCAs ; k++)
		fprintf(out, " %10.5f", data[i][k]);
	fprintf(out, "\n");
	}
	fclose(out);
	
	}

	strcpy( newname, name );
	strcat( newname, ".ps");
	
	out = fopen( newname, "w" );
	if ( out == NULL )
		{
		printf("\033[31m\033[1mCan not open postscript file for writing. Abort.\n");
		myexit(1);
		}
	if ( VERBOSE )
		printf("Writing postscript file %s.\n", newname );

	fprintf(out, "%%!PS-Adobe-1.0\n");
	fprintf(out, "%%%%Creator: carma\n");
	fprintf(out, "%%%%BoundingBox: 23 27 569 573\n");
	fprintf(out, "%%%%Orientation: Portrait\n");
	fprintf(out, "%%%%EndComments\n");
	fprintf(out, "\n%%%%\n%%%% %s\n%%%%", pscomment);
	fprintf(out, "\n\n");
	fprintf(out, "gsave 28 28 translate 540 540 scale\n");
	fprintf(out, "/picstr %d string def %d %d 8 [ %d 0 0 %d 0 %d ]\n", nofCAs, nofCAs, nofCAs, nofCAs, -nofCAs, nofCAs );
	fprintf(out, "{ currentfile picstr readhexstring pop }\n");
	fprintf(out, "image\n");

	scale = 255.0 / (gmax - gmin) ;
	for ( i=1 ; i <= nofCAs ; i++)
	for ( k=1 ; k <= nofCAs ; k++ )
	{
	val = data[i][k];
	gray = (int)( (val - gmin) * scale + 0.500 );
	if ( gray < 0 )
		gray = 0;
	if ( gray > 255 )
		gray = 255;
	if ( REVERSE == YES )
		gray = 255 -gray;
	fprintf(out, "%02X", gray );
        if ( ++line_indicator > 39 )
        	{
       			fprintf( out, "\n");
     			line_indicator = 0;
     				}
	}


	fprintf(out, "\ngrestore 0.1 setlinewidth 28 28 moveto 28 568 lineto 568 568 lineto 568 28 lineto closepath stroke\n");

	i = 1;
	for ( val = 28.0 + 0.50*(540.0 / nofCAs) ; val < 568 ; val += (540.0 / nofCAs) )
	{
		if ( i % 10 == 0 )
	    		{
	    			fprintf(out, "%f 568 moveto %f 572 lineto stroke\n", val, val);
	    			fprintf(out, "24 %f moveto 28 %f lineto stroke\n", 568 + 28.0 - val, 568 + 28.0 - val);
            		}
            	else
            		{
	    			fprintf(out, "%f 568 moveto %f 570 lineto stroke\n", val, val);
	    			fprintf(out, "26 %f moveto 28 %f lineto stroke\n", 568 + 28.0 - val, 568 + 28.0 - val);
          		}
		i++;
	     
	}
	      

	fprintf(out, "showpage\n");
	fclose(out);
	return;
}












/*****************************************************************************************************************************/
/**   Write postscript file of the data in **data, using a color gradient                                                   **/
/*****************************************************************************************************************************/

void 	wps_color( data, name )
float	**data;
char	name[];
{
	FILE	*out;
	char 	newname[300];
	int	i, k;
	float	val;
	int	gm, gf;
        int  	count;
        int   	r, g, b;
                                	
	
	

        if ( SIGMOIDAL == YES )
        {
	if ( VERBOSE )
		printf("Values will be weighted with a sigmoidal function (l=%f).\n", LAMBDA );
	for ( i=1 ; i <= nofCAs ; i++)
	for ( k=1 ; k <= nofCAs ; k++)
		data[i][k] = ((2.0 / (1.0+exp(-LAMBDA*data[i][k]))) - 1.0);	
	}


	if ( WRITE_DATA == YES )
	{
	strcpy( newname, name );
	strcat( newname, ".dat");
	out = fopen( newname, "w" );
        if ( out == NULL )
                {
                printf("\033[31m\033[1mCan not open data file for writing. Abort.\n");
                myexit(1);
                }
	if ( VERBOSE )
		printf("Writing data (formatted ASCII) to the file %s.\n", newname );

	for ( i=1 ; i <= nofCAs ; i++)
	{
	for ( k=1 ; k <= nofCAs ; k++)
		fprintf(out, " %10.5f", data[i][k]);
	fprintf(out, "\n");
	}
	fclose(out);
	
	}

	strcpy( newname, name );
	strcat( newname, ".ps");
	
	out = fopen( newname, "w" );
	if ( out == NULL )
		{
		printf("\033[31m\033[1mCan not open postscript file for writing. Abort.\n");
		myexit(1);
		}
	if ( VERBOSE )
		printf("Writing postscript file %s.\n", newname );








	fprintf(out, "%%!PS-Adobe-1.0\n");
	fprintf(out, "%%%%Creator: carma\n");
	fprintf(out, "%%%%BoundingBox: 23 27 569 573\n");
	fprintf(out, "%%%%Orientation: Portrait\n");
	fprintf(out, "%%%%EndComments\n");
	fprintf(out, "\n%%%%\n%%%% %s\n%%%%", pscomment);
	fprintf(out, "\n\n");
        fprintf(out, "/M { moveto } def\n/C { lineto stroke newpath } def\n");
	fprintf(out, "0.8 setlinewidth\n");
	fprintf(out, "gsave 28 568 translate 540 -540 scale\n");
	fprintf(out, "/DataString %d string def\n", nofCAs );
	fprintf(out, "%d %d 8 [ %d 0 0 %d 0 0 ]\n", nofCAs, nofCAs, nofCAs, nofCAs );
	fprintf(out, "{ currentfile DataString readhexstring pop }\nfalse 3\ncolorimage\n");
	count = 0;
	for ( gm=1 ; gm <= nofCAs ; gm++ )
	for ( gf=1 ; gf <= nofCAs   ; gf++ )
		{
			getcol( (data[gm][gf]-gmin)/(gmax-gmin), &r, &g, &b );
			if ( r < 0 )
				r = 0;
			if ( r > 255 )
				r = 255;
			if ( g < 0 )
				g = 0;
			if ( g > 255 )
				g = 255;
			if ( b < 0 )
				b = 0;
			if ( b > 255 )
				b = 255;

			fprintf(out, "%02x%02x%02x", (unsigned char)(r), (unsigned char)(g), (unsigned char)(b) );
			count++;
			if ( count == 10 )
				{
					fprintf(out, "\n");
					count = 0;
							}
								}
								

	fprintf(out, "\ngrestore 0.1 setlinewidth 28 28 moveto 28 568 lineto 568 568 lineto 568 28 lineto closepath stroke\n");

	i = 1;
	for ( val = 28.0 + 0.50*(540.0 / nofCAs) ; val < 568 ; val += (540.0 / nofCAs) )
	{
		if ( i % 10 == 0 )
	    		{
	    			fprintf(out, "%f 568 moveto %f 572 lineto stroke\n", val, val);
	    			fprintf(out, "24 %f moveto 28 %f lineto stroke\n", 568 + 28.0 - val, 568 + 28.0 - val);
            		}
            	else
            		{
	    			fprintf(out, "%f 568 moveto %f 570 lineto stroke\n", val, val);
	    			fprintf(out, "26 %f moveto 28 %f lineto stroke\n", 568 + 28.0 - val, 568 + 28.0 - val);
          		}
		i++;
	     
	}
	      

	fprintf(out, "showpage\n");
	fclose(out);
	return;
}




void getcol( float val, int *r, int *g, int *b )
{

	if  ( REVERSE == YES )
		val = 1.0 - val;

	if ( val <= 0.25 )
		{
			*r = 255 * ( 4.0 * val * (RED_2 - RED_1) + RED_1 ); 
			*g = 255 * ( 4.0 * val * (GREEN_2 - GREEN_1) + GREEN_1 ); 
			*b = 255 * ( 4.0 * val * (BLUE_2 - BLUE_1) + BLUE_1 ); 
		}
	else if ( val <= 0.50 )
		{
			*r = 255 * ( 4.0 * (val - 0.250) * (RED_3 - RED_2) + RED_2 ); 
			*g = 255 * ( 4.0 * (val - 0.250) * (GREEN_3 - GREEN_2) + GREEN_2 ); 
			*b = 255 * ( 4.0 * (val - 0.250) * (BLUE_3 - BLUE_2) + BLUE_2 ); 
		}
	else if ( val <= 0.75 )
		{
			*r = 255 * ( 4.0 * (val - 0.500) * (RED_4 - RED_3) + RED_3 ); 
			*g = 255 * ( 4.0 * (val - 0.500) * (GREEN_4 - GREEN_3) + GREEN_3 ); 
			*b = 255 * ( 4.0 * (val - 0.500) * (BLUE_4 - BLUE_3) + BLUE_3 ); 
		}
	else
		{
			*r = 255 * ( 4.0 * (val - 0.750) * (RED_5 - RED_4) + RED_4 ); 
			*g = 255 * ( 4.0 * (val - 0.750) * (GREEN_5 - GREEN_4) + GREEN_4 ); 
			*b = 255 * ( 4.0 * (val - 0.750) * (BLUE_5 - BLUE_4) + BLUE_4 ); 
		}

}        




/*****************************************************************************************************************************/
/**   Read CA coordinates from a .pdb file                                                                                  **/
/*****************************************************************************************************************************/

int	get_pdb_coords( name )
char	name[];
{
	FILE 	*in;
	char	string[300];	
	float	x, y, z;
	int	nof = 0;	
        char    num[9];
        int	natm;
        
        
	in = fopen( name, "r" );
	if ( in == NULL )
		{
			printf("\033[31m\033[1mCan not open .pdb file for read. Abort.\n");
			myexit( 1 );
					}

	
        while ( fgets( string, 299, in ) != NULL )                              /* for all ATOM lines in input file */
        	{								/* containing the search string CA at */
        									/* the right place */
        	for ( natm = 0 ; natm < strlen( ATOMID) / 5 ; natm++ )								
		if ( strncasecmp(string, "ATOM", 4) == 0 && (strncasecmp( &string[12], &ATOMID[natm*5], 5) == 0 || ALL_ATID == YES || (HEAVY==YES && strncasecmp( &string[13], "H", 1) != 0) ))
		{
                x = atof( strncpy( &num[0], &string[30], 8 ));          	/* read x y z and store them */
                y = atof( strncpy( &num[0], &string[38], 8 ));
                z = atof( strncpy( &num[0], &string[46], 8 ));
		CAs[nof][0] = x;
		CAs[nof][1] = y;
		CAs[nof][2] = z;
		nof++;
		if ( nof == MAX_NOF_CAS - 1 )
			{
				printf("\033[31mMaximum number of atoms exceeded. Change MAX_NOF_CAS and re-compile.\033[0m\n");
				myexit(1);
						}
				}	
					}
	fclose( in );	
	return( nof );
}








/*****************************************************************************************************************************/
/**   Public domain  memory allocation routines from Numerical recipes.                                                     **/
/*****************************************************************************************************************************/

float *vector(long nl, long nh)
/* allocate a float vector with subscript range v[nl..nh] */
{
        float *v;

        v=(float *)malloc((size_t) ((nh-nl+1+NR_END)*sizeof(float)));
        if (!v) nrerror("allocation failure in vector()");
        return v-nl+NR_END;
}

void free_vector(float *v, long nl, long nh)
/* free a float vector allocated with vector() */
{
        free((FREE_ARG) (v+nl-NR_END));
}

void    	nrerror( char error_text[])
{
	printf("\n\n%s\n\n", &error_text[0] );
	myexit( 1 );
}

float	**matrix( long nrl, long nrh, long ncl, long nch )
{
	long 	i, nrow=nrh-nrl+1, ncol=nch-ncl+1;
	float	**m;

	m = (float **)malloc((size_t)((nrow+NR_END)*sizeof(float*)));
	if (!m) nrerror("allocation failure 1 in matrix()");
	m += NR_END;
	m -= nrl;
	m[nrl] = (float *)malloc((size_t)((nrow*ncol+NR_END)*sizeof(float)));
	if (!m[nrl]) nrerror("allocate failure 2 in matrix()");
	m[nrl] += NR_END;
	m[nrl] -= ncl;

	for (i=nrl+1 ; i <= nrh ; i++ )
		m[i] = m[i-1] + ncol;

	return m;
}

float	***f3tensor(long nrl, long nrh, long ncl, long nch, long ndl, long ndh )
{
	long 	i, j, nrow=nrh-nrl+1, ncol=nch-ncl+1, ndep = ndh-ndl+1;
	float	***t;

	t=(float ***)malloc((size_t)((nrow+NR_END)*sizeof(float**)));
	if (!t) nrerror("allocation failure 1 in f3tensor()");
	t += NR_END;
	t -= nrl;

	t[nrl] = (float **)malloc((size_t)((nrow*ncol+NR_END)*sizeof(float *)));
	if ( !t[nrl] ) nrerror("allocation failure 2 in f3tensor()");
	t[nrl] += NR_END;
	t[nrl] -= ncl;
	
	t[nrl][ncl] = (float *)malloc((size_t)((nrow*ncol*ndep + NR_END)*sizeof(float)));
	if (!t[nrl][ncl] ) nrerror("allocation failure 3 in f3tensor()");
	t[nrl][ncl] += NR_END;
	t[nrl][ncl] -= ndl;

	for( j=ncl+1 ; j <= nch ; j++ )
		t[nrl][j] = t[nrl][j-1] + ndep;
	for ( i=nrl+1 ; i <= nrh ; i++ )
		{
		t[i] = t[i-1] + ncol;
		t[i][ncl] = t[i-1][ncl] + ncol * ndep;
		for ( j=ncl+1 ; j <= nch ; j++ )
			t[i][j] = t[i][j-1] + ndep;
                                              	}

	return t;
}


unsigned short int	***int3tensor(long nrl, long nrh, long ncl, long nch, long ndl, long ndh )
{
	long 	i, j, nrow=nrh-nrl+1, ncol=nch-ncl+1, ndep = ndh-ndl+1;
	unsigned short int	***t;

	t=(unsigned short int ***)calloc((size_t)((nrow+NR_END)), sizeof(unsigned short int**));
	if (!t) nrerror("allocation failure 1 in intf3tensor()");
	t += NR_END;
	t -= nrl;

	t[nrl] = (unsigned short int **)calloc((size_t)((nrow*ncol+NR_END)), sizeof(unsigned short int *));
	if ( !t[nrl] ) nrerror("allocation failure 2 in intf3tensor()");
	t[nrl] += NR_END;
	t[nrl] -= ncl;
	
	t[nrl][ncl] = (unsigned short int *)calloc((size_t)((nrow*ncol*ndep + NR_END)), sizeof(unsigned short int));
	if (!t[nrl][ncl] ) nrerror("allocation failure 3 in intf3tensor()");
	t[nrl][ncl] += NR_END;
	t[nrl][ncl] -= ndl;

	for( j=ncl+1 ; j <= nch ; j++ )
		t[nrl][j] = t[nrl][j-1] + ndep;
	for ( i=nrl+1 ; i <= nrh ; i++ )
		{
		t[i] = t[i-1] + ncol;
		t[i][ncl] = t[i-1][ncl] + ncol * ndep;
		for ( j=ncl+1 ; j <= nch ; j++ )
			t[i][j] = t[i][j-1] + ndep;
                                              	}

	return t;
}





void free_matrix(float **m, long nrl, long nrh, long ncl, long nch)
/* free a float matrix allocated by matrix() */
{
        free((FREE_ARG) (m[nrl]+ncl-NR_END));
        free((FREE_ARG) (m+nrl-NR_END));
}

void free_f3tensor(float ***t, long nrl, long nrh, long ncl, long nch,
        long ndl, long ndh)
/* free a float f3tensor allocated by f3tensor() */
{
        free((FREE_ARG) (t[nrl][ncl]+ndl-NR_END));
        free((FREE_ARG) (t[nrl]+ncl-NR_END));
        free((FREE_ARG) (t+nrl-NR_END));
}

void free_int3tensor(int ***t, long nrl, long nrh, long ncl, long nch,
        long ndl, long ndh)
/* free a float f3tensor allocated by f3tensor() */
{
        free((FREE_ARG) (t[nrl][ncl]+ndl-NR_END));
        free((FREE_ARG) (t[nrl]+ncl-NR_END));
        free((FREE_ARG) (t+nrl-NR_END));
}



/*****************************************************************************************************************************/
/**   END of Public domain  memory allocation routines from Numerical recipes.                                              **/
/*****************************************************************************************************************************/









void	filter()
{
	float	**m1;
	float	**m2;
	float	*p1;
	float	*p2;
	int	i;
	float	dmin, dmax;
	int	INCR = 100;
	int	SIZE = 300;
	int	ndata = 0;
	float	val;
	int	ret = 1;
	
							/* allocate a starting piece of memory */
						
	m1 = matrix( 1, SIZE, 1, SIZE);
	p1 = &m1[1][1];
							/* outer loop reallocates & de-allocates memory segments to */
							/* satisfy memory requirements */
	
	while( ret != EOF )
	{
		if ( ndata > 0 )
			{
				m2 = matrix( 1, SIZE+INCR, 1, SIZE+INCR);
				p2 = &m2[1][1];
				memcpy( p2, p1, SIZE*SIZE*sizeof(float) );		
				free_matrix( m1, 1, SIZE, 1, SIZE );
				m1 = m2;
				p1 = p2;
				SIZE = SIZE+INCR;
						}
		

							/* inner loop fills the currently allocated memory */
	while ( (ret = scanf( "%f", &val )) == 1 )
		{
			p1[ndata] = val;	
			ndata++;
			if ( ndata == SIZE*SIZE )
				break;
					}
						}
						
	nofCAs = (int)(sqrt( (double)(ndata) ) + 0.500 );	
	if ( nofCAs * nofCAs != ndata )
		{
			printf("\033[31m\033[1mThe %d values read-in do not make a square matrix.\033[0m\n", ndata);
			myexit( 1 );
					}

	m2 = matrix( 1, nofCAs, 1, nofCAs);
	p2 = &m2[1][1];
	memcpy( p2, p1, nofCAs*nofCAs*sizeof(float) );		
	free_matrix( m1, 1, SIZE, 1, SIZE );
	m1 = m2;
	p1 = p2;



	dmax = -10000000000000.0;
	dmin =  10000000000000.0;
	for ( i=0 ; i < ndata ; i++ )
		{
			if ( (val = p1[i]) > dmax )
				dmax = val;
				
			if ( val < dmin )
				dmin = val;
						}
									

	if ( HAVE_MIN == NO )
		gmin = dmin;
	if ( HAVE_MAX == NO )
		gmax = dmax;

	if ( COLOUR ==  NO )
	{
	if ( REVERSE == NO )
		printf("\033[32mWill plot the gradient from %f (white) to %f (black).\033[0m\n", gmin, gmax );
	else
		printf("\033[32mWill plot the gradient from %f (black) to %f (white).\033[0m\n", gmin, gmax );

	REVERSE = !REVERSE;

	}
	else
		printf("\033[32mWill plot the gradient from %f to %f using colour postscript.\033[0m\n", gmin, gmax );
	


	wps( m1, "carma.stdin" );
	

/**********************************************************************************************************/
/** Ok. Since we are here, add the possibility to calculate eigenvalues and eigenvectors of the matrix.  **/
/** If the matrix is not symmetric the user will get what he/she deserves.                               **/
/**********************************************************************************************************/	

#if defined (LAPACK) || defined (NR)

	if ( EIGEN == YES )
	{
	printf("\033[37m\033[1mEigenvalues and eigenvectors of the input matrix will be calculated.\n");
	printf("If the input matrix is not symmetric you will get \033[31m\033[1mwrong\033[37m\033[1m results.\033[0m\n");
	
	eigendim = nofCAs;
				
	eigen( m1 );
	}

#endif


	myexit( 0 );


}






void	mergeps( name1, name2 )
char 	*name1, *name2;
{
	FILE 	*in1, *in2;
	FILE 	*out;
	char	string1[300];	
	char	string2[300];	
	int	size;
	char	junk[50];
	int	x, y;
	int	c11, c12, c13, c14, c15, c16; 
	int	c21, c22, c23, c24, c25, c26;
	int	ISCOLOUR = NO;
	
	
	in1 = fopen( name1, "r" );
	in2 = fopen( name2, "r" );
	out = fopen( "carma.merged.ps", "w");
	
	if ( in1 == NULL )
		{
			printf("\033[31m\033[1mCan not open the file \"%s\" for read. Abort.\n", name1 );
			myexit( 1 );
					}
	if ( in2 == NULL )
		{
			printf("\033[31m\033[1mCan not open the file \"%s\" for read. Abort.\n", name2 );
			myexit( 1 );
					}
	if ( out == NULL )
		{
			printf("\033[31m\033[1mCan not open the carma.merged.ps file for output. Abort.\n");
			myexit( 1 );
					}

        while ( fgets( string1, 299, in1 ) != NULL && fgets( string2, 299, in2 ) != NULL )
        	{
        	if ( strcmp( string1, string2 ) != 0 )
        		{
        		printf("\033[31m\033[1mThe postscript files' headers differ. Abort.\033[0m\n");
        		myexit(1);
        			}
        	fprintf(out, "%s", string1 );

		if ( strncmp( string1, "/picstr", 7 ) == 0 )
			sscanf( string1, "%s %d", junk, &size );
			
		if ( strncmp( string1, "/DataString", 11 ) == 0 )
			{
				sscanf( string1, "%s %d", junk, &size );
				ISCOLOUR = YES;
			}
		
        	if ( 	strncmp( string1, "image", 5 ) == 0 ||
        		strncmp( string1, "colorimage", 10 ) == 0	)
        		break;
        	}



								/* You wont believe this ... */
	if ( ISCOLOUR == NO )
	{
	for ( x=1 ; x <= size ; x++ )
	for ( y=1 ; y <= size ; y++ )
	{
	c11 = getc(in1);
	if ( c11 == '\n' )
		c11 = getc(in1);
	c12 = getc(in1);
	c21 = getc(in2);
	if ( c21 == '\n' )
		c21 = getc(in2);
	c22 = getc(in2);
	
 	if ( c11 == EOF || c12 == EOF || c21 == EOF || c22 == EOF )
 		{
 			printf("\033[31m\033[1mUnexpected end of file encountered. Abort.\033[0m\n");
 			myexit( 1 );
 					}
	if ( y >= x )
		{
			putc( c11, out );
			putc( c12, out );
						}
	else 	
		{
			putc( c21, out );
			putc( c22, out );
						}
	if ( (y + (x-1)*size) % 40 == 0 )
		putc( '\n', out );
	
	}
	}
	else
	{
	for ( x=1 ; x <= size ; x++ )
	for ( y=1 ; y <= size ; y++ )
	{
	c11 = getc(in1);
	if ( c11 == '\n' )
		c11 = getc(in1);
	c12 = getc(in1);
	c13 = getc(in1);
	c14 = getc(in1);
	c15 = getc(in1);
	c16 = getc(in1);
	c21 = getc(in2);
	if ( c21 == '\n' )
		c21 = getc(in2);
	c22 = getc(in2);
	c23 = getc(in2);
	c24 = getc(in2);
	c25 = getc(in2);
	c26 = getc(in2);
	
 	if ( 	c11 == EOF || c12 == EOF || c13 == EOF || c14 == EOF || c15 == EOF || c16 == EOF ||
 		c21 == EOF || c22 == EOF || c23 == EOF || c24 == EOF || c25 == EOF || c26 == EOF )
 		{
 			printf("\033[31m\033[1mUnexpected end of file encountered. Abort.\033[0m\n");
 			myexit( 1 );
 					}
	if ( y >= x )
		{
			putc( c11, out );
			putc( c12, out );
			putc( c13, out );
			putc( c14, out );
			putc( c15, out );
			putc( c16, out );
						}
	else 	
		{
			putc( c21, out );
			putc( c22, out );
			putc( c23, out );
			putc( c24, out );
			putc( c25, out );
			putc( c26, out );
						}
	if ( (y + (x-1)*size) % 40 == 0 )
		putc( '\n', out );
	
	}
	}
	
	
	
	
        while ( fgets( string1, 299, in1 ) != NULL && fgets( string2, 299, in2 ) != NULL )
        	fprintf(out, "%s", string1 );
	

	myexit( 0 );

}





/*****************************************************************************************************************************/
/**	This routine will re-order the frames contained in a DCD file to match an ordered list of frame indeces       	    **/
/** 	(one-offset) that are contained in the file pointed by "listname"						    **/
/*****************************************************************************************************************************/

void	sortdcd( dcdname, listname )
char	*dcdname;
char 	*listname;
{
	FILE	*list;
	int	dcd;
	int	outdcd;
	char	dcd_head[92];
	char	dcd_head2[16];
	char	title[81];
	char	string[300];
	int	frame;
	off_t	start;
	char	*outdcdhead;
	int	i;
	int	frames_written;
	
	unsigned int	nofatoms;
	unsigned int	auint;
	unsigned int	headerframes;
	unsigned int	bytes_per_set;
	
	
	
	
	list = fopen( listname, "r" );
	if ( list == NULL )
		{
			printf("\033[31m\033[1mCan not open file containing the frame number order.\033[0m\n");
			myexit(1);
					}
	
#ifdef WINDOWS
	dcd = open( dcdname, O_RDONLY | O_BINARY | O_RANDOM );
#else
	dcd = open( dcdname, O_RDONLY );
#endif

	if ( dcd == -1 )
		{
			printf("\033[31m\033[1mCan not open DCD file for read. Abort.\033[0m\n");
			myexit( 1 );
					}

	if ( read( dcd, dcd_head, (size_t)(92) ) != 92 )
		{
			printf("\033[31m\033[1mPremature EOF for DCD file ? Abort.\033[0m\n");
			myexit(1);
					}

	if ( strncasecmp( (char *)(&dcd_head[4]), "CORD", 4) != 0 )
		{
			printf("\033[31m\033[1mNot a coordinate DCD file ? Abort.\033[0m\n");
			myexit(1);
					}

	if ( (unsigned int)(*((unsigned int *)(&dcd_head[48]))) == 1 )
		{
			HAVE_CELL = YES;
			CELL_OFFSET = 14;
			if ( VERBOSE )
				printf("\033[32m\033[1mIt appears that this DCD file contains unit cell information.\033[0m\n");
					}

	if ( (unsigned int)(*((unsigned int *)(&dcd_head[52]))) == 1 )
		{
			printf("\033[31m\033[1mIt appears that this is a CHARMM-specific DCD file. Abort.\033[0m\n");
			myexit(1);
					}
	
	
	headerframes = (unsigned int)(*((unsigned int *)(&dcd_head[8])));
	
	if ( VERBOSE )
	{				
	printf("Number of coordinate sets is %d\n", *((unsigned int *)(&dcd_head[8])));
	printf("Starting timestep         is %d\n", *((unsigned int *)(&dcd_head[12])));
	printf("Timesteps between sets    is %d\n", *((unsigned int *)(&dcd_head[16])));
	}
	
	if ( read( dcd, &auint, (size_t)(4) ) != 4 )
		{
			printf("\033[31m\033[1mPremature EOF for DCD file ? Abort.\033[0m\n");
			myexit(1);
					}
	if ( read( dcd, &auint, (size_t)(4) ) != 4 )
		{
			printf("\033[31m\033[1mPremature EOF for DCD file ? Abort.\033[0m\n");
			myexit(1);
					}
	if ( auint > 0 && VERBOSE )
		printf("Titles : \n");
		
	for ( i=0 ; i < auint ; i++ )
		{
		if ( read( dcd, &title, (size_t)(80) ) != 80 )
		{
			printf("\033[31m\033[1mPremature EOF for DCD file ? Abort.\033[0m\n");
			myexit(1);
					}
		title[80] = 0;
		if ( VERBOSE )
			printf("%s\n", title );
		}

	if ( read( dcd, dcd_head2, (size_t)(16) ) != 16 )
		{
			printf("\033[31m\033[1mPremature EOF for DCD file ? Abort.\033[0m\n");
			myexit(1);
					}

	nofatoms = (unsigned int)(*((unsigned int *)(&dcd_head2[8])));
	
	if ( VERBOSE )
		printf("Number of atoms in sets   is %d\n", nofatoms);

	
								/* Allocate enough memory */
	if ( HAVE_CELL == YES )
	{
	bytes_per_set = (unsigned int)(3 * ( 4 * nofatoms + 8 ) + 56);
	}
	else
	{
	bytes_per_set = (unsigned int)(3 * ( 4 * nofatoms + 8 ));
	}

	dcd_frame = vector( 1, bytes_per_set / 4 );


	start = lseek( dcd, (off_t)(0), SEEK_CUR );



#ifdef WINDOWS
	outdcd = open( "carma.reordered.dcd", O_WRONLY | O_CREAT | O_TRUNC | O_BINARY | O_RANDOM, S_IRUSR | S_IWUSR );
#else
	outdcd = open( "carma.reordered.dcd", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP );
#endif
	if ( outdcd == -1 )
		{
			printf("\033[31m\033[1mCan not open DCD file for output. Abort.\033[0m\n");
			myexit( 1 );
					}
	outdcdhead = malloc( (size_t)(start) );
	if ( lseek( dcd, (off_t)(0), SEEK_SET ) == (off_t)(-1) )
		{
			printf("\033[31m\033[1mCan not seek back to the beginning of file ? Abort.\033[0m\n");
			myexit(1);
					}
	if ( (off_t)(read( dcd, outdcdhead, (size_t)(start) )) != start )
		{
			printf("\033[31m\033[1mPremature EOF for DCD file ? Abort.\033[0m\n");
			myexit(1);
					}
	if ( (off_t)(write( outdcd, outdcdhead, (size_t)(start) )) != start )
		{
			printf("\033[31m\033[1mFailed to write header block to DCD file ? Abort.\033[0m\n");
			myexit(1);
					}



	frames_written = 0;
        while ( fgets( string, 299, list ) != NULL )
	{
	
	frame = atoi( string ) - 1;
	if ( frame < 0 )
		{
			printf("\033[31m\033[1mFrame numbers must be positive integers greater than zero.\033[0m\n");
			myexit(1);
					}
	if ( lseek( dcd, (off_t)(start), SEEK_SET ) == (off_t)(-1) )
		{
			printf("\033[31m\033[1mCan not seek the beginning of data ? Abort.\033[0m\n");
			myexit(1);
					}
	if ( lseek( dcd, (off_t)(bytes_per_set * (off_t)(frame)), SEEK_CUR ) == (off_t)(-1) )
		{
			printf("\033[31m\033[1mRequested frame not present ? Abort.\033[0m\n");
			myexit(1);
					}
	if ( (unsigned int)(read( dcd, (void *)(&dcd_frame[1]), (size_t)(bytes_per_set) )) != bytes_per_set )
		{
			printf("\033[31m\033[1mRequested frame not found. Abort.\033[0m\n");
			myexit(1);
					}
	if ( (unsigned int)(write( outdcd, (void *)(&dcd_frame[1]), (size_t)(bytes_per_set) )) != bytes_per_set )
		{
			printf("\033[31m\033[1mFailed to write frame %d to DCD file.\033[0m\n", frame );
			myexit(1);
					}
	
	frames_written++;
	}
	



	if ( frames_written != headerframes )
	{
	
	if ( VERBOSE )
	printf("\033[32m\033[1mWrote %d frames out of %d in the DCD file.\033[0m\n", frames_written, headerframes);

	if ( lseek( dcd, (off_t)(0), SEEK_SET ) == (off_t)(-1) )
		{
			printf("\033[31m\033[1mCan not seek back to the beginning of file ? Abort.\033[0m\n");
			myexit(1);
					}
	if ( lseek( outdcd, (off_t)(0), SEEK_SET ) == (off_t)(-1) )
		{
			printf("\033[31m\033[1mCan not seek back to the beginning of file ? Abort.\033[0m\n");
			myexit(1);
					}
	if ( (off_t)(read( dcd, outdcdhead, (size_t)(start) )) != start )
		{
			printf("\033[31m\033[1mPremature EOF for DCD file ? Abort.\033[0m\n");
			myexit(1);
					}

	*((unsigned int *)(&outdcdhead[8])) = (unsigned int)(frames_written);


	if ( (off_t)(write( outdcd, outdcdhead, (size_t)(start) )) != start )
		{
			printf("\033[31m\033[1mFailed to write header block to DCD file ? Abort.\033[0m\n");
			myexit(1);
					}

	}



	close(dcd);
	close(outdcd);
	fclose(list);


	myexit( 0 );


}







/*****************************************************************************************************************************/
/**	Eigenvector and eigenvalue calculation : if we have LAPACK use it ...						    **/
/*****************************************************************************************************************************/

#ifdef LAPACK

void	eigen( data )
float	**data;
{
	int	i, k;
	FILE	*out;
	float	*extra;
	float	temp;
  	int 	JOBZ='V';
  	int	UPLO='U';
  	int	N;
  	int	LDA;
  	int	LWORK;
	int	INFO;
	FILE	*in;


	eigenvalues = vector( 1 , eigendim );

	
	if ( USE_LAST == YES )
	{
	printf("\033[37m\033[1mRe-using eigenvalues and eigenvectors from previous run.\033[0m\n");


	eigenvectors = data;

	if ( DPCA == NO )
		in = fopen( "carma.PCA.eigenvectors.dat", "r" );
	else
		in = fopen( "carma.dPCA.eigenvectors.dat", "r" );


	if ( in == NULL )
		{
		printf("\033[31m\033[1mCan not read eigenvectors file. Abort.\033[0m\n");
		myexit(1);
			}
	for ( i=1 ; i <= eigendim ; i++)
	for ( k=1 ; k <= eigendim ; k++)
		if ( fscanf(in, "%f", &eigenvectors[i][k]) != 1 )
			{
			printf("\033[31m\033[1mFailure while reading from the eigenvectors file. Abort.\033[0m\n");
			myexit(1);
			}

	fclose(in);


	if ( DPCA == NO )
		in = fopen( "carma.PCA.eigenvalues.dat", "r" );
	else
		in = fopen( "carma.dPCA.eigenvalues.dat", "r" );


        if ( in == NULL )
                {
                printf("\033[31m\033[1mCan not open eigenvalues file. Abort.\033[0m\n");
                myexit(1);
                        }

	for ( i=1 ; i <= eigendim ; i++ )
		if ( fscanf(in, "%f", &eigenvalues[i] ) != 1 )
                        {
                        printf("\033[31m\033[1mFailure while reading from the eigenvalues file. Abort.\033[0m\n");
                        myexit(1);
                        }


	fclose(in);

	return;
		
	}

  	
  	N = eigendim;
  	LDA = eigendim;
	
	extra = vector( 1 , 1 );


	if ( VERBOSE )
		printf("Calculation of eigenvectors and eigenvalues ...\n");

	if ( VERBOSE )
		printf("Asking for optimal workspace size : ");

	LWORK = -1;
	ssyev_( &JOBZ, &UPLO, &N, &data[1][1], &LDA, &eigenvalues[1], &extra[1], &LWORK, &INFO);
	LWORK = (int)(extra[1]);

	free_vector( extra, 1, 1 );
	extra = vector( 1 , LWORK );
	
	if ( VERBOSE )
		printf("%d\nStarting the calculation ...\n", LWORK );
	
	ssyev_( &JOBZ, &UPLO, &N, &data[1][1], &LDA, &eigenvalues[1], &extra[1], &LWORK, &INFO);
  	if ( INFO != 0 ) 
  		{
    			printf("\033[31m\033[1mError in LAPACK ssyev() call: %d\033[0m\n",INFO);
			myexit(1);
  					}

	if ( VERBOSE) 
		printf("Done. Now sorting ... ");

        free_vector( extra, 1, LWORK );
	

        for ( i=0 ; i < eigendim/2 ; i++ )
                {
                        temp = eigenvalues[1+i];
                        eigenvalues[1+i] = eigenvalues[eigendim-i];
                        eigenvalues[eigendim-i] = temp;
                                                        }
 

	eigenvectors = matrix( 1, eigendim, 1, eigendim);

	for ( i=1 ; i <= eigendim ; i++ )
	for ( k=1 ; k <= eigendim ; k++ )
		eigenvectors[k][eigendim-i+1] = data[i][k];


	if ( DPCA == NO )
		out = fopen( "carma.PCA.eigenvectors.dat", "w" );
	else
		out = fopen( "carma.dPCA.eigenvectors.dat", "w" );


	if ( out == NULL )
		{
		printf("\033[31m\033[1mCan not open eigenvectors file for output. Abort.\033[0m\n");
		myexit(1);
		}
	for ( i=1 ; i <= eigendim ; i++)
	{
	for ( k=1 ; k <= eigendim ; k++)
		fprintf(out, " %15.10f", eigenvectors[i][k]);
	fprintf(out, "\n");
	}
	fclose(out);

	if ( DPCA == NO )
		out = fopen( "carma.PCA.eigenvalues.dat", "w" );
	else
		out = fopen( "carma.dPCA.eigenvalues.dat", "w" );

        if ( out == NULL )
                {
                printf("\033[31m\033[1mCan not open eigenvalues file for output. Abort.\033[0m\n");
                myexit(1);
                }
	for ( i=1 ; i <= eigendim ; i++ )
		fprintf(out, " %15.10f\n", eigenvalues[i] );
	fclose(out);

	if ( ENTROPY == YES )
	{
	double	entropy;

	for ( i=1 ; i <= eigendim -6 ; i++ )
		if ( eigenvalues[i] <= 0.0 )
			break;

#ifndef WINDOWS
	if ( i == eigendim -5 )
	{
	entropy = 0.0;
	for ( i=1 ; i <= eigendim -6 ; i++ )
		entropy += ( sqrt( CONST1 / ( Temp * eigenvalues[i] ) ) / expm1( sqrt( CONST1 / ( Temp * eigenvalues[i] ) ))
                           - log( -expm1( -sqrt( CONST1 / ( Temp * eigenvalues[i] ))) ));
	entropy *= (AVOGADRO * KBOL);

	printf("\nEntropy (Andricioaei) is %f (J/molK) \n", entropy );
	}
	else
	{
	printf("\nThe Andricioaei entropy can not be calculated due to\nthe presence of an eigenvalue less than or equal to zero\n" );
	}
#endif


	entropy = 0.0;
	for ( i=1 ; i <= eigendim -6 ; i++ )
		entropy += log1p( CONST2 * Temp * M_E * M_E * eigenvalues[i] );
	
	entropy *= (AVOGADRO * 0.50 * KBOL );
	
	printf("Entropy (Schlitter)   is %f (J/molK) \n", entropy );


	}

	if ( VERBOSE )
		printf("done.\n");

	return;
}

#endif







/*****************************************************************************************************************************/
/**	, else, we will use (but of course, not release) the NR subroutines						    **/
/*****************************************************************************************************************************/

#ifdef NR

void eigsrt(d,v,n)
float **v,d[];
int n;
{
	int k,j,i;
	float p;

	for (i=1;i<n;i++) {
		p=d[k=i];
		for (j=i+1;j<=n;j++)
			if (d[j] >= p) p=d[k=j];
		if (k != i) {
			d[k]=d[i];
			d[i]=p;
			for (j=1;j<=n;j++) {
				p=v[j][i];
				v[j][i]=v[j][k];
				v[j][k]=p;
			}
		}
	}
}

void tred2(a,n,d,e)
float **a,d[],e[];
int n;
{
	int l,k,j,i;
	float scale,hh,h,g,f;

	for (i=n;i>=2;i--) {
		l=i-1;
		h=scale=0.0;
		if (l > 1) {
			for (k=1;k<=l;k++)
				scale += fabs(a[i][k]);
			if (scale == 0.0)
				e[i]=a[i][l];
			else {
				for (k=1;k<=l;k++) {
					a[i][k] /= scale;
					h += a[i][k]*a[i][k];
				}
				f=a[i][l];
				g=(f >= 0.0 ? -sqrt(h) : sqrt(h));
				e[i]=scale*g;
				h -= f*g;
				a[i][l]=f-g;
				f=0.0;
				for (j=1;j<=l;j++) {
					a[j][i]=a[i][j]/h;
					g=0.0;
					for (k=1;k<=j;k++)
						g += a[j][k]*a[i][k];
					for (k=j+1;k<=l;k++)
						g += a[k][j]*a[i][k];
					e[j]=g/h;
					f += e[j]*a[i][j];
				}
				hh=f/(h+h);
				for (j=1;j<=l;j++) {
					f=a[i][j];
					e[j]=g=e[j]-hh*f;
					for (k=1;k<=j;k++)
						a[j][k] -= (f*e[k]+g*a[i][k]);
				}
			}
		} else
			e[i]=a[i][l];
		d[i]=h;
	}
	d[1]=0.0;
	e[1]=0.0;

	for (i=1;i<=n;i++) {
		l=i-1;
		if (d[i]) {
			for (j=1;j<=l;j++) {
				g=0.0;
				for (k=1;k<=l;k++)
					g += a[i][k]*a[k][j];
				for (k=1;k<=l;k++)
					a[k][j] -= g*a[k][i];
			}
		}
		d[i]=a[i][i];
		a[i][i]=1.0;
		for (j=1;j<=l;j++) a[j][i]=a[i][j]=0.0;
	}
}




void tqli(d,e,n,z)
float **z,d[],e[];
int n;
{
	float pythag();
	int m,l,iter,i,k;
	float s,r,p,g,f,dd,c,b;

	for (i=2;i<=n;i++) e[i-1]=e[i];
	e[n]=0.0;
	for (l=1;l<=n;l++) {
		iter=0;
		do {
			for (m=l;m<=n-1;m++) {
				dd=fabs(d[m])+fabs(d[m+1]);
				if ((float)(fabs(e[m])+dd) == dd) break;
			}
			if (m != l) {
				if (iter++ == 30) nrerror("Too many iterations in tqli");
				g=(d[l+1]-d[l])/(2.0*e[l]);
				r=pythag(g,1.0);
				g=d[m]-d[l]+e[l]/(g+SIGN(r,g));
				s=c=1.0;
				p=0.0;
				for (i=m-1;i>=l;i--) {
					f=s*e[i];
					b=c*e[i];
					e[i+1]=(r=pythag(f,g));
					if (r == 0.0) {
						d[i+1] -= p;
						e[m]=0.0;
						break;
					}
					s=f/r;
					c=g/r;
					g=d[i+1]-p;
					r=(d[i]-g)*s+2.0*c*b;
					d[i+1]=g+(p=s*r);
					g=c*r-b;
					for (k=1;k<=n;k++) {
						f=z[k][i+1];
						z[k][i+1]=s*z[k][i]+c*f;
						z[k][i]=c*z[k][i]-s*f;
					}
				}
				if (r == 0.0 && i >= l) continue;
				d[l] -= p;
				e[l]=g;
				e[m]=0.0;
			}
		} while (m != l);
	}
}



float pythag(a,b)
float a,b;
{
	float absa,absb;
	absa=fabs(a);
	absb=fabs(b);
	if (absa > absb) return absa*sqrt(1.0+SQRNR(absb/absa));
	else return (absb == 0.0 ? 0.0 : absb*sqrt(1.0+SQRNR(absa/absb)));
}




/********************** END OF NR ************************/






void	eigen( data )
float	**data;
{
	int	i, k;
	FILE	*out;
	float	*extra;
	FILE	*in;


	eigenvalues = vector( 1 , eigendim );

	
	if ( USE_LAST == YES )
	{
	printf("\033[37m\033[1mRe-using eigenvalues and eigenvectors from previous run.\033[0m\n");

	eigenvectors = data;

	if ( DPCA == NO )
		in = fopen( "carma.PCA.eigenvectors.dat", "r" );
	else
		in = fopen( "carma.dPCA.eigenvectors.dat", "r" );


	if ( in == NULL )
		{
		printf("\033[31m\033[1mCan not read eigenvectors file. Abort.\033[0m\n");
		myexit(1);
			}
	for ( i=1 ; i <= eigendim ; i++)
	for ( k=1 ; k <= eigendim ; k++)
		if ( fscanf(in, "%f", &eigenvectors[i][k]) != 1 )
			{
			printf("\033[31m\033[1mFailure while reading from the eigenvectors file. Abort.\033[0m\n");
			myexit(1);
			}

	fclose(in);


	if ( DPCA == NO )
		in = fopen( "carma.PCA.eigenvalues.dat", "r" );
	else
		in = fopen( "carma.dPCA.eigenvalues.dat", "r" );
	

        if ( in == NULL )
                {
                printf("\033[31m\033[1mCan not open eigenvalues file. Abort.\033[0m\n");
                myexit(1);
                        }

	for ( i=1 ; i <= eigendim ; i++ )
		if ( fscanf(in, "%f", &eigenvalues[i] ) != 1 )
                        {
                        printf("\033[31m\033[1mFailure while reading from the eigenvalues file. Abort.\033[0m\n");
                        myexit(1);
                        }


	fclose(in);

	return;
		
	}
	
	extra = vector( 1 , eigendim );
	
	if ( VERBOSE )
		printf("Calculation of eigenvectors and eigenvalues ...\n");


	tred2( data, eigendim, eigenvalues, extra );
	tqli( eigenvalues, extra, eigendim, data );

	eigenvectors = data;

	if ( VERBOSE) 
		printf("Done. Sorting ...\n" );

	eigsrt( eigenvalues, eigenvectors, eigendim );

	if ( DPCA == NO )
		out = fopen( "carma.PCA.eigenvectors.dat", "w" );
	else
		out = fopen( "carma.dPCA.eigenvectors.dat", "w" );
	

        if ( out == NULL )
                {
                printf("\033[31m\033[1mCan not open eigenvectors file for output. Abort.\033[0m\n");
                myexit(1);
                }

	for ( i=1 ; i <= eigendim ; i++)
	{
	for ( k=1 ; k <= eigendim ; k++)
		fprintf(out, " %15.10f", eigenvectors[i][k]);
	fprintf(out, "\n");
	}
	fclose(out);


	if ( DPCA == NO )
		out = fopen( "carma.PCA.eigenvalues.dat", "w" );
	else	
		out = fopen( "carma.dPCA.eigenvalues.dat", "w" );

        if ( out == NULL )
                {
                printf("\033[31m\033[1mCan not open eigenvalues file for output. Abort.\033[0m\n");
                myexit(1);
                }
	for ( i=1 ; i <= eigendim ; i++ )
		fprintf(out, " %15.10f\n", eigenvalues[i] );
	fclose(out);

	if ( ENTROPY == YES )
	{
	double	entropy;

	for ( i=1 ; i <= eigendim -6 ; i++ )
		if ( eigenvalues[i] <= 0.0 )
			break;

#ifndef WINDOWS
	if ( i == eigendim -5 )
	{
	entropy = 0.0;
	for ( i=1 ; i <= eigendim -6 ; i++ )
		entropy += ( sqrt( CONST1 / ( Temp * eigenvalues[i] ) ) / expm1( sqrt( CONST1 / ( Temp * eigenvalues[i] ) ))
                           - log( -expm1( -sqrt( CONST1 / ( Temp * eigenvalues[i] ))) ));
	entropy *= (AVOGADRO * KBOL);

	printf("\nEntropy (Andricioaei) is %f (J/molK) \n", entropy );
	}
	else
	{
	printf("\nThe Andricioaei entropy can not be calculated due to\nthe presence of an eigenvalue less than or equal to zero\n" );
	}
#endif


	entropy = 0.0;
	for ( i=1 ; i <= eigendim -6 ; i++ )
		entropy += log1p( CONST2 * Temp * M_E * M_E * eigenvalues[i] );
	
	entropy *= (AVOGADRO * 0.50 * KBOL );
	
	printf("Entropy (Schlitter)   is %f (J/molK) \n", entropy );


	}

	return;
}


#endif














/*****************************************************************************************************************************/
/**	This is Kabsch's lsqfit algorithm as implemented by David Hinds and slightly modified (to the worse) for carma 	    **/
/*****************************************************************************************************************************/


static int solve(double e[3],
                   double e0, double det, double spur, double cof)
  {
  double d, h, g, cth, sth, sqrth;
#define epsilon 1.0e-37
#define sqrt3 1.7320508075688772
  
  det *= det;
  d = SQR(spur);
  h = d - cof;
  g = spur * (cof*1.5 - d) - det*0.5;
  if (h > d*epsilon) {
    sqrth = SQRTABS(h);
    d = -g/(h*sqrth);
    if (d > 1-epsilon) {    /* Two identical roots */
      e[0] = spur + 2*sqrth;
      e[2] = e[1] = spur - sqrth;
      return 2;
      }
    else if (d < -1+epsilon) {    /* Two identical roots */ 
      e[1] = e[0] = spur+sqrth;
      e[2] = MAX(0, spur - 2*sqrth);
      return 3;
      }
    else {    /* Three distinct roots */
      d = acos(d)/3.0;
      cth = sqrth*cos(d); sth = sqrth*sqrt3*sin(d);
      e[0] = spur + 2*cth;
      e[1] = spur - cth + sth;
      e[2] = MAX(0, spur - cth - sth);
      return 1;
      }
    }
  else {    /* Three identical roots */ 
    e[0] = e[1] = e[2] = spur;
    return 4;
    }

  } /* solve */
  
static void hinds_matrix(rotate_t u, xlate_t t,
                   int sw, double e[3], double rr[6], double r[3][3],
                   double sx[3], double sy[3], int npts)
  {
  double ss[6], d, h, p, a[3][3], b[3][3];
  int i, j, l, m, m1, m2, m3;

  if (sw == 4) {
    /* Case of three identical roots */
    for (i = 0; i < 3; i++)
      for (j = 0; j < 3; j++)
        if (i == j) a[i][j] = 1.0; else a[i][j] = 0.0;
    }
  else {
    if (sw == 1) {
      /* Case of three distinct roots */
      for (l=0; l < 2; l++) {
        d = e[l];
        ss[0] = (d-rr[2]) * (d-rr[5]) - SQR(rr[4]);
        ss[1] = (d-rr[5]) * rr[1] + rr[3]*rr[4];
        ss[2] = (d-rr[0]) * (d-rr[5]) - SQR(rr[3]);
        ss[3] = (d-rr[2]) * rr[3] + rr[1]*rr[4];
        ss[4] = (d-rr[0]) * rr[4] + rr[1]*rr[3];
        ss[5] = (d-rr[0]) * (d-rr[2]) - SQR(rr[1]);
        if (FABS(ss[0]) >= FABS(ss[2])) {
          if (FABS(ss[0]) >= FABS(ss[5])) {
            a[0][l] = ss[0]; a[1][l] = ss[1]; a[2][l] = ss[3];
            }
          else {
            a[0][l] = ss[3]; a[1][l] = ss[4]; a[2][l] = ss[5];
            }
          }
        else if (FABS(ss[2]) >= FABS(ss[5])) {
          a[0][l] = ss[1]; a[1][l] = ss[2]; a[2][l] = ss[4];
          }
        else {
          a[0][l] = ss[3]; a[1][l] = ss[4]; a[2][l] = ss[5];
          }
        d = sqrt(SQR(a[0][l]) + SQR(a[1][l]) + SQR(a[2][l]));
        a[0][l] /= d; a[1][l] /= d; a[2][l] /= d;
        }
      m1 = 2; m2 = 0; m3 = 1;
      }
    else {
      /* Cases of two distinct roots */
      if (sw == 2) {
        m = 0; m1 = 2; m2 = 0; m3 = 1;
        }
      else {
        m = 2; m1 = 0; m2 = 1; m3 = 2;
        }
      h = e[2];
      a[0][1] = 1.0; a[1][1] = 1.0; a[2][1] = 1.0;
      if (FABS(rr[0]-h) > FABS(rr[2]-h)) {
        if (FABS(rr[0]-h) > FABS(rr[5]-h)) {
          a[0][m] = rr[0]-h; a[1][m] = rr[1]; a[2][m] = rr[3];
          p = -(rr[0] + rr[1] + rr[3] - h);
          a[0][1] = p/a[0][m];
          }
        else {
          a[0][m] = rr[3]; a[1][m] = rr[4]; a[2][m] = rr[5]-h;
          p = -(rr[3] + rr[4] + rr[5] - h);
          a[2][1] = p/a[2][m];
          }
        }
      else {
        if (FABS(rr[2]-h) > FABS(rr[5]-h)) {
          a[0][m] = rr[1]; a[1][m] = rr[2]-h; a[2][m] = rr[4];
          p = -(rr[1] + rr[2] + rr[4] - h);
          a[1][1] = p/a[1][m];
          }
        else {
          a[0][m] = rr[3]; a[1][m] = rr[4]; a[2][m] = rr[5]-h;
          p = -(rr[3] + rr[4] + rr[5] - h);
          a[2][1] = p/a[2][m];
          }
        }
      d = sqrt(SQR(a[0][m]) + SQR(a[1][m]) + SQR(a[2][m]));
      p = sqrt(SQR(a[0][1]) + SQR(a[1][1]) + SQR(a[2][1]));
      for (i = 0; i < 3; i++) {
        a[i][1] /= p;
        a[i][m] /= d;
        }
      }
    /* Common for either two or three distinct roots */
    a[0][m1] = a[1][m2]*a[2][m3] - a[1][m3]*a[2][m2];
    a[1][m1] = a[2][m2]*a[0][m3] - a[2][m3]*a[0][m2];
    a[2][m1] = a[0][m2]*a[1][m3] - a[0][m3]*a[1][m2];
    }
  
  for (l = 0; l < 2; l++) {
    d = 0;
    for (i = 0; i < 3; i++) {
      b[i][l] = r[0][i]*a[0][l] + r[1][i]*a[1][l] + r[2][i]*a[2][l];
      d += SQR(b[i][l]);
      }
    d = sqrt(d);
    if (d == 0) {
    			printf("\033[31m\033[1mRotation matrix determination failed. Abort.\033[0m\n");
    			myexit(1);
    					}
    					
    for (i = 0; i < 3; i++) b[i][l] /= d;
    }
  b[0][2] = b[1][0]*b[2][1] - b[1][1]*b[2][0];
  b[1][2] = b[2][0]*b[0][1] - b[2][1]*b[0][0];
  b[2][2] = b[0][0]*b[1][1] - b[0][1]*b[1][0];
  
  /* Calculate rotation matrix */
  for (i = 0; i < 3; i++)
    for (j = 0; j < 3; j++)
      u[i][j] = b[i][0]*a[j][0] + b[i][1]*a[j][1] + b[i][2]*a[j][2];
  /* Calculate translation vector */
  for (i = 0; i < 3; i++)
    t[i] = (sy[i] - u[i][0]*sx[0] - u[i][1]*sx[1] - u[i][2]*sx[2])/npts;
  }

double vsumby3(const float v[], unsigned int n)
  {
  double sum;
  unsigned int i;
# ifdef _UNROLL
  unsigned int j;
#endif

  sum = *v; n--; v += 3;
# ifdef _UNROLL
  j = n & 7;
  for (i = 0; i != j; i++, v += 3) sum += *v;
  for ( ; i != n; i += 8, v += 24)
    sum += (double)v[0] + (double)v[3] +
           (double)v[6] + (double)v[9] +
           (double)v[12] + (double)v[15] +
           (double)v[18] + (double)v[21];
#else
  for (i = 0; i != n; i++, v += 3) sum += *v;
#endif
  return sum;
  }

double vsumsqr(const float v[], unsigned int n)
  {
  double sum;
  unsigned int i;
# ifdef _UNROLL
  unsigned int j;
#endif
  
  sum = DSQR(*v); n--; v++;
# ifdef _UNROLL
  j = n & 7;
  for (i = 0; i != j; i++, v++) sum += DSQR(*v);
  for ( ; i != n; i += 8, v += 8)
    sum += DSQR(v[0]) + DSQR(v[1]) + DSQR(v[2]) + DSQR(v[3]) +
           DSQR(v[4]) + DSQR(v[5]) + DSQR(v[6]) + DSQR(v[7]);
# else
  for (i = 0; i != n; i++, v++) sum += DSQR(*v);
# endif
  return sum;
  }

double vdotby3(const float a[], const float b[], unsigned int n)
  {
  double sum;
  unsigned int i;
# ifdef _UNROLL
  unsigned int j;
#endif
  
  sum = (double)(*a) * (double)(*b); n--; a += 3; b += 3;
# ifdef _UNROLL
  j = n & 7;
  for (i = 0; i != j; i++, a += 3, b += 3)
    sum += (double)(*a) * (double)(*b);
  for ( ; i != n; i += 8, a += 24, b += 24)
    sum += ((double)a[0] * (double)b[0] +
            (double)a[3] * (double)b[3] +
            (double)a[6] * (double)b[6] +
            (double)a[9] * (double)b[9] +
            (double)a[12] * (double)b[12] +
            (double)a[15] * (double)b[15] +
            (double)a[18] * (double)b[18] +
            (double)a[21] * (double)b[21]);
# else
  for (i = 0; i != n; i++, a += 3, b += 3)
    sum += (double)(*a) * (double)(*b);
# endif
  return sum;
  }





float bestfit(rotate_t u, xlate_t t,
                float *a, float *b, int npts)
  {
  double sx[3], sy[3], sxy[3][3], sx2, sy2;
  double r[3][3], rr[6];
  double d, spur, det, cof, e0, e[3], inpts;
  int i, j, m, sw;
  float	*aa=0, *bb=0;
	

	if ( HAVE_INDEX == YES )
	{
	FILE	*indeces;
	int	index[MAX_NOF_CAS];
	int	i, j;
	char    string[300];
	char	junk[300];

	indeces = fopen("fit.index", "r");
	if ( indeces == NULL )
		{	
			printf("\033[31m\033[1m\nCan not open the 'fit.index' file. Abort.\033[0m\n");
			myexit(1);
					}

	i = 0;
        while ( fgets( string, 299, indeces ) != NULL )
		{
			if ( sscanf( string, "%s", junk) == 1 ) 	/* If its not an empty line ... */
			{	

			if ( sscanf( string, "%d", &index[i]) != 1 )
				{	
					printf("\033[31m\033[1mThe 'fit.index' file is not valid. Abort.\033[0m\n");
					myexit(1);
							}
			index[i] = index[i] - 1;
			if ( index[i] < 0 )
				{
					printf("\033[31m\033[1mNOTE : carma expects 1-based indeces in the fit.index file.\033[0m\n");
					myexit(1);
							}

			if ( index[i] >= npts )
				{	
					printf("\033[31m\033[1mToo large index in the 'fit.index' file. Abort.\033[0m\n");
					myexit(1);
							}
			i++;
			}
		}

	fclose( indeces );

	if ( i > npts )
		{	
			printf("\033[31m\033[1mToo many indeces in the 'fit.index' file. Abort.\033[0m\n");
			myexit(1);
					}

	aa = vector( 1, 3*i );
	bb = vector( 1, 3*i );

	for ( j=0 ; j < i ; j++ )
		{
			aa[j*3+1] = a[index[j]*3+0];		
			aa[j*3+2] = a[index[j]*3+1];		
			aa[j*3+3] = a[index[j]*3+2];		

			bb[j*3+1] = b[index[j]*3+0];		
			bb[j*3+2] = b[index[j]*3+1];		
			bb[j*3+3] = b[index[j]*3+2];		
				}

	a = &aa[1];
	b = &bb[1];
	npts = i;
	}	
	
  sx[0] = vsumby3(&a[0+0], npts);
  sx[1] = vsumby3(&a[0+1], npts);
  sx[2] = vsumby3(&a[0+2], npts);
  sy[0] = vsumby3(&b[0+0], npts);
  sy[1] = vsumby3(&b[0+1], npts);
  sy[2] = vsumby3(&b[0+2], npts);
  sx2 = vsumsqr(&a[0], 3*npts);
  sy2 = vsumsqr(&b[0], 3*npts);
  sxy[0][0] = vdotby3(&a[0], &b[0], npts);
  sxy[0][1] = vdotby3(&a[0], &b[1], npts);
  sxy[0][2] = vdotby3(&a[0], &b[2], npts);
  sxy[1][0] = vdotby3(&a[1], &b[0], npts);
  sxy[1][1] = vdotby3(&a[1], &b[1], npts);
  sxy[1][2] = vdotby3(&a[1], &b[2], npts);
  sxy[2][0] = vdotby3(&a[2], &b[0], npts);
  sxy[2][1] = vdotby3(&a[2], &b[1], npts);
  sxy[2][2] = vdotby3(&a[2], &b[2], npts);


  inpts = 1.0/npts;
  e0 = (sx2 - (SQR(sx[0])+SQR(sx[1])+SQR(sx[2]))*inpts +
        sy2 - (SQR(sy[0])+SQR(sy[1])+SQR(sy[2]))*inpts)*inpts;

  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      r[i][j] = (sxy[i][j] - sx[i]*sy[j]*inpts)*inpts;
      }
    }
    
  for (m = j = 0; j < 3; j++) {
    for (i = 0; i <= j; i++,m++) {
      rr[m] = r[i][0]*r[j][0] + r[i][1]*r[j][1] + r[i][2]*r[j][2];
      }
    }

  det = r[0][0] * (r[1][1]*r[2][2] - r[2][1]*r[1][2])
      - r[1][0] * (r[0][1]*r[2][2] - r[2][1]*r[0][2])
      + r[2][0] * (r[0][1]*r[1][2] - r[1][1]*r[0][2]);

  spur = (rr[0]+rr[2]+rr[5])/3.0;
  cof = (rr[2]*rr[5] - SQR(rr[4]) + rr[0]*rr[5] -
         SQR(rr[3]) + rr[0]*rr[2] - SQR(rr[1]))/3.0;


  sw = solve(e, e0, det, spur, cof);
	
	if ( sw != 1 )
		{
                printf("\033[31m\033[1mInternal problem with bestfit(). Please report.\033[0m\n");
		myexit( 1 );
                }


  hinds_matrix(u, t, sw, e, rr, r, sx, sy, npts);
  d = SQRTABS(e[2]);
  if (det < 0) d = -d;
  d += SQRTABS(e[1]) + SQRTABS(e[0]);
  d = e0-2*d;

	if ( HAVE_INDEX == YES )
		{
			free_vector( aa, 1, 3*npts );
			free_vector( bb, 1, 3*npts );
					}

  return SQRTABS(d);

  } /* bestfit */









void myexit( val )
int     val;
{

#ifdef GRA
	if ( GRAPHICS && YGL_INIT )
	winclose( winid );
#endif

        exit( val );
}













#ifdef GRA

void	static_view()
{
	int	i;
	int	do_redraw;
        double l,m,n;
        double cosk, sink;
	static double a1=1.0, a2=0.0, a3=0.0, a4=0.0, a5=1.0, a6=0.0, a7=0.0, a8=0.0, a9=1.0;
	static double aa1=1.0, aa2=0.0, aa3=0.0, aa4=0.0, aa5=1.0, aa6=0.0, aa7=0.0, aa8=0.0, aa9=1.0;
	double x, y, z;
	int	c;
	static int	framerate = 0;
	static time_t	t0, t1;
	static unsigned long 	sleeper=0;
	

	
	do_redraw = NO;

	if ( PACKING_FIRST ) 
		{
			a1 = 1.0;
			a2 = 0.0;
			a3 = 0.0;
			a4 = 0.0;
			a5 = 1.0;
			a6 = 0.0;
			a7 = 0.0;
			a8 = 0.0;
			a9 = 1.0;
			
			aa1 = 1.0;
			aa2 = 0.0;
			aa3 = 0.0;
			aa4 = 0.0;
			aa5 = 1.0;
			aa6 = 0.0;
			aa7 = 0.0;
			aa8 = 0.0;
			aa9 = 1.0;
			
			do_redraw = YES;
			PACKING_FIRST = NO;
		}


	if ( (c = getbutton(ESCKEY)) || now_playing )
	{

	do_redraw = YES;
	usleep( sleeper );

	if ( framerate == 0 )
		t0 = time( NULL );

	if ( framerate >= 0 )
		framerate++;

	if ( framerate == 120 )
		{

		t1 = time( NULL );
		if ( (t1-t0) >= 2 )
			{
				framerate = -1;
			}
		else
			{
			sleeper += 20000;
			framerate = 0;
			}
			}		

	if ( c )
		{
			if ( ! now_playing )
				{
					now_playing = YES;
					usleep(200000);
				}
			else
				{
					now_playing = NO;
					do_redraw = NO;
					usleep(200000);
				}
		}


	kappa += dkappa;
	omega += domega;
	phi += dphi;

        l = sin(omega)*cos(phi);
        m = sin(omega)*sin(phi);
        n = cos(omega);
        cosk = cos( kappa );
        sink = sin( kappa );

        a1 = l*l+(m*m+n*n)*cosk;
        a2 = l*m*(1.0-cosk)-n*sink;
        a3 = n*l*(1.0-cosk)+m*sink;
        a4 = l*m*(1.0-cosk)+n*sink;
        a5 = m*m+(l*l+n*n)*cosk;
        a6 = m*n*(1.0-cosk)-l*sink;
        a7 = n*l*(1.0-cosk)-m*sink;
        a8 = m*n*(1.0-cosk)+l*sink;
        a9 = n*n+(l*l+m*m)*cosk;

	for ( i=0 ; i < nofCAs ; i++ )
		{
			x = CAs[i][0];
			y = CAs[i][1];
			z = CAs[i][2];
			cCAs[i][0] = a1*x + a2*y + a3*z;
			cCAs[i][1] = a4*x + a5*y + a6*z;
			cCAs[i][2] = a7*x + a8*y + a9*z;
		}
	}


	if ( getbutton(XKEY) )
		{
		GRA_VIEW = 1;
		do_redraw = YES;
		}
	else if ( getbutton(YKEY) )
		{
		GRA_VIEW = 2;
		do_redraw = YES;
		}
	else if ( getbutton(ZKEY) )
		{
		GRA_VIEW = 3;
		do_redraw = YES;
		}

        if ( getbutton( WKEY ) )
                {
                FILE    *outPDB;
                
                gl2ppm("carma_image.ppm");

		outPDB = fopen( "carma_frame.pdb", "w");
		if ( outPDB == NULL )
			{	
				printf("\033[31m\033[1mCan not open output file. Abort.\033[0m\n");
				myexit(1);
						}

		if ( HAVE_CELL == YES )
			fprintf(outPDB,"CRYST1%9.3f%9.3f%9.3f%7.2f%7.2f%7.2f P 1           1\n", 
					cell_a, cell_b, cell_c, cell_alpha, cell_beta, cell_gamma );

		for ( i=0 ; i < nofCAs ; i++ )
			fprintf(outPDB, "ATOM% 7d  %s %s %s%4d    % 8.3f% 8.3f% 8.3f  1.00  0.00\n", 
				i+1, str_atname[i], str_resname[i], str_segname[i], str_resid[i],
				CAs[i][0], CAs[i][1], CAs[i][2] );

		fprintf( outPDB, "END\n");
		fclose( outPDB );
                        
		sleep( 1 );
                }


	if ( getbutton(SKEY) )
		{
		usleep(200000);
		if ( STEREO == NO )
			{
				STEREO = YES;
				do_redraw = YES;
			        color(0);
				linewidth( 1 );
				move2(-CROSS,0.0);
				draw2(CROSS,0.0);
				move2(0.0,-CROSS);
				draw2(0.0,CROSS);
				linewidth( LINEW );

			}
		else
			{
				STEREO = NO;
				do_redraw = YES;
			        color(1);
				linewidth( 1 );
				move2(-CROSS,0.0);
				draw2(CROSS,0.0);
				move2(0.0,-CROSS);
				draw2(0.0,CROSS);
				linewidth( LINEW );


			}
		}

	if ( getbutton(PERIODKEY) )
		{
			do_redraw = YES;
			if ( GRABOX > 1.10 )
				GRABOX *= 0.9500;
			ortho2( -GRABOX/2.0, GRABOX/2.0, -GRABOX/2.0, GRABOX/2.0);
				}			
	if ( getbutton(COMMAKEY) )
		{
			do_redraw = YES;
			GRABOX *= 1.0500;
			ortho2( -GRABOX/2.0, GRABOX/2.0, -GRABOX/2.0, GRABOX/2.0);
				}			
        if ( getbutton(EQUALKEY) )
                {
                        STEP *= 2;
                                        }
        if ( getbutton(MINUSKEY) )
                {              
                        STEP /= 2;
                        if ( STEP < 1 )
                                STEP = 1;
                                                }

	if ( getbutton(RIGHTARROWKEY) )
		{	
			do_redraw = YES;
			XOFFSET += GRABOX * 0.0200;
				}			
	if ( getbutton(LEFTARROWKEY) )
		{
			do_redraw = YES;
			XOFFSET -= GRABOX * 0.0200;
				}			
	if ( getbutton(UPARROWKEY) )
		{
			do_redraw = YES;
			YOFFSET += GRABOX * 0.0200;
				}			
	if ( getbutton(DOWNARROWKEY) )
		{
			do_redraw = YES;
			YOFFSET -= GRABOX * 0.0200;
				}			
	if ( getbutton(RKEY) )
		{
			do_redraw = YES;
			YOFFSET = 0.0;
			XOFFSET = 0.0;
				}			

	if ( ! do_redraw && ! now_playing )
		{
		usleep( 100 );
		return;
		}


	if ( STEREO )
		{
		if ( GRA_VIEW == 3 )
			{
			viewport(1,299,1,600);
			ortho2( -GRABOX/4.0, GRABOX/4.0, -GRABOX/2.0, GRABOX/2.0);
			}
		else
			{
			viewport(302,600,1,600);
			ortho2( -GRABOX/4.0, GRABOX/4.0, -GRABOX/2.0, GRABOX/2.0);
			}

	        color(1);
		linewidth( 1 );
		move2(-CROSS,0.0);
		draw2(CROSS,0.0);
		move2(0.0,-CROSS);
		draw2(0.0,CROSS);
		linewidth( LINEW );

	
		}



	for ( i=0 ; i < nofCAs ; i++ )
	{
	color(colorindex[i]);

	if ( GRA_VIEW == 3 )
		pnt2(cCAs[i][0]+XOFFSET, cCAs[i][1]+YOFFSET);
	else if ( GRA_VIEW == 1 )
		pnt2(cCAs[i][1]+XOFFSET, cCAs[i][2]+YOFFSET);
	else
		pnt2(cCAs[i][2]+XOFFSET, cCAs[i][0]+YOFFSET);
	}




	if ( PACKING )
	{

	for ( i=0 ; i < nofCAs ; i++ )
	{
	float	x, y, z;
	float	xx, yy, zz;

	color(255);

	x = cCAs[i][0];
	y = cCAs[i][1];
	z = cCAs[i][2];
	
        xx = x + a1*orthom00+a2*orthom01+a3*orthom02;
        yy = y + a4*orthom00+a5*orthom01+a6*orthom02;
        zz = z + a7*orthom00+a8*orthom01+a9*orthom02;

	if ( GRA_VIEW == 3 )
		pnt2(xx+XOFFSET, yy+YOFFSET);
	else if ( GRA_VIEW == 1 )
		pnt2(yy+XOFFSET, zz+YOFFSET);
	else
		pnt2(zz+XOFFSET, xx+YOFFSET);

        xx = x + a1*orthom10+a2*orthom11+a3*orthom12;
        yy = y + a4*orthom10+a5*orthom11+a6*orthom12;
        zz = z + a7*orthom10+a8*orthom11+a9*orthom12;

	if ( GRA_VIEW == 3 )
		pnt2(xx+XOFFSET, yy+YOFFSET);
	else if ( GRA_VIEW == 1 )
		pnt2(yy+XOFFSET, zz+YOFFSET);
	else
		pnt2(zz+XOFFSET, xx+YOFFSET);

        xx = x + a1*orthom20+a2*orthom21+a3*orthom22;
        yy = y + a4*orthom20+a5*orthom21+a6*orthom22;
        zz = z + a7*orthom20+a8*orthom21+a9*orthom22;

	if ( GRA_VIEW == 3 )
		pnt2(xx+XOFFSET, yy+YOFFSET);
	else if ( GRA_VIEW == 1 )
		pnt2(yy+XOFFSET, zz+YOFFSET);
	else
		pnt2(zz+XOFFSET, xx+YOFFSET);




        xx = x + a1*orthom00+a2*orthom01+a3*orthom02+ a1*orthom10+a2*orthom11+a3*orthom12;
        yy = y + a4*orthom00+a5*orthom01+a6*orthom02+ a4*orthom10+a5*orthom11+a6*orthom12;
        zz = z + a7*orthom00+a8*orthom01+a9*orthom02+ a7*orthom10+a8*orthom11+a9*orthom12;

	if ( GRA_VIEW == 3 )
		pnt2(xx+XOFFSET, yy+YOFFSET);
	else if ( GRA_VIEW == 1 )
		pnt2(yy+XOFFSET, zz+YOFFSET);
	else
		pnt2(zz+XOFFSET, xx+YOFFSET);

        xx = x + a1*orthom10+a2*orthom11+a3*orthom12+ a1*orthom20+a2*orthom21+a3*orthom22;
        yy = y + a4*orthom10+a5*orthom11+a6*orthom12+ a4*orthom20+a5*orthom21+a6*orthom22;
        zz = z + a7*orthom10+a8*orthom11+a9*orthom12+ a7*orthom20+a8*orthom21+a9*orthom22;

	if ( GRA_VIEW == 3 )
		pnt2(xx+XOFFSET, yy+YOFFSET);
	else if ( GRA_VIEW == 1 )
		pnt2(yy+XOFFSET, zz+YOFFSET);
	else
		pnt2(zz+XOFFSET, xx+YOFFSET);

        xx = x + a1*orthom20+a2*orthom21+a3*orthom22+ a1*orthom00+a2*orthom01+a3*orthom02;
        yy = y + a4*orthom20+a5*orthom21+a6*orthom22+ a4*orthom00+a5*orthom01+a6*orthom02;
        zz = z + a7*orthom20+a8*orthom21+a9*orthom22+ a7*orthom00+a8*orthom01+a9*orthom02;

	if ( GRA_VIEW == 3 )
		pnt2(xx+XOFFSET, yy+YOFFSET);
	else if ( GRA_VIEW == 1 )
		pnt2(yy+XOFFSET, zz+YOFFSET);
	else
		pnt2(zz+XOFFSET, xx+YOFFSET);


        xx = x + a1*orthom20+a2*orthom21+a3*orthom22+ a1*orthom00+a2*orthom01+a3*orthom02+ a1*orthom10+a2*orthom11+a3*orthom12;
        yy = y + a4*orthom20+a5*orthom21+a6*orthom22+ a4*orthom00+a5*orthom01+a6*orthom02+ a4*orthom10+a5*orthom11+a6*orthom12;
        zz = z + a7*orthom20+a8*orthom21+a9*orthom22+ a7*orthom00+a8*orthom01+a9*orthom02+ a7*orthom10+a8*orthom11+a9*orthom12;

	if ( GRA_VIEW == 3 )
		pnt2(xx+XOFFSET, yy+YOFFSET);
	else if ( GRA_VIEW == 1 )
		pnt2(yy+XOFFSET, zz+YOFFSET);
	else
		pnt2(zz+XOFFSET, xx+YOFFSET);



	}


	for ( i=0 ; i < realCAscount ; i++ )
	{
	float	x, y, z;
	float	xx, yy, zz;

	if ( GRADIENT )
		color(colorindex[i*nofCAs/realCAscount]);
	else
		color(colorindex[realCAs[i]]);

	x = cCAs[realCAs[i]][0];
	y = cCAs[realCAs[i]][1];
	z = cCAs[realCAs[i]][2];
	
        xx = x + a1*orthom00+a2*orthom01+a3*orthom02;
        yy = y + a4*orthom00+a5*orthom01+a6*orthom02;
        zz = z + a7*orthom00+a8*orthom01+a9*orthom02;

	if ( GRA_VIEW == 3 )
		circf(xx+XOFFSET, yy+YOFFSET, 0.50);
	else if ( GRA_VIEW == 1 )
		circf(yy+XOFFSET, zz+YOFFSET, 0.50);
	else
		circf(zz+XOFFSET, xx+YOFFSET, 0.50);

        xx = x + a1*orthom10+a2*orthom11+a3*orthom12;
        yy = y + a4*orthom10+a5*orthom11+a6*orthom12;
        zz = z + a7*orthom10+a8*orthom11+a9*orthom12;

	if ( GRA_VIEW == 3 )
		circf(xx+XOFFSET, yy+YOFFSET, 0.50);
	else if ( GRA_VIEW == 1 )
		circf(yy+XOFFSET, zz+YOFFSET, 0.50);
	else
		circf(zz+XOFFSET, xx+YOFFSET, 0.50);

        xx = x + a1*orthom20+a2*orthom21+a3*orthom22;
        yy = y + a4*orthom20+a5*orthom21+a6*orthom22;
        zz = z + a7*orthom20+a8*orthom21+a9*orthom22;

	if ( GRA_VIEW == 3 )
		circf(xx+XOFFSET, yy+YOFFSET, 0.50);
	else if ( GRA_VIEW == 1 )
		circf(yy+XOFFSET, zz+YOFFSET, 0.50);
	else
		circf(zz+XOFFSET, xx+YOFFSET, 0.50);




        xx = x + a1*orthom00+a2*orthom01+a3*orthom02+ a1*orthom10+a2*orthom11+a3*orthom12;
        yy = y + a4*orthom00+a5*orthom01+a6*orthom02+ a4*orthom10+a5*orthom11+a6*orthom12;
        zz = z + a7*orthom00+a8*orthom01+a9*orthom02+ a7*orthom10+a8*orthom11+a9*orthom12;

	if ( GRA_VIEW == 3 )
		circf(xx+XOFFSET, yy+YOFFSET, 0.50);
	else if ( GRA_VIEW == 1 )
		circf(yy+XOFFSET, zz+YOFFSET, 0.50);
	else
		circf(zz+XOFFSET, xx+YOFFSET, 0.50);

        xx = x + a1*orthom10+a2*orthom11+a3*orthom12+ a1*orthom20+a2*orthom21+a3*orthom22;
        yy = y + a4*orthom10+a5*orthom11+a6*orthom12+ a4*orthom20+a5*orthom21+a6*orthom22;
        zz = z + a7*orthom10+a8*orthom11+a9*orthom12+ a7*orthom20+a8*orthom21+a9*orthom22;

	if ( GRA_VIEW == 3 )
		circf(xx+XOFFSET, yy+YOFFSET, 0.50);
	else if ( GRA_VIEW == 1 )
		circf(yy+XOFFSET, zz+YOFFSET, 0.50);
	else
		circf(zz+XOFFSET, xx+YOFFSET, 0.50);

        xx = x + a1*orthom20+a2*orthom21+a3*orthom22+ a1*orthom00+a2*orthom01+a3*orthom02;
        yy = y + a4*orthom20+a5*orthom21+a6*orthom22+ a4*orthom00+a5*orthom01+a6*orthom02;
        zz = z + a7*orthom20+a8*orthom21+a9*orthom22+ a7*orthom00+a8*orthom01+a9*orthom02;

	if ( GRA_VIEW == 3 )
		circf(xx+XOFFSET, yy+YOFFSET, 0.50);
	else if ( GRA_VIEW == 1 )
		circf(yy+XOFFSET, zz+YOFFSET, 0.50);
	else
		circf(zz+XOFFSET, xx+YOFFSET, 0.50);


        xx = x + a1*orthom20+a2*orthom21+a3*orthom22+ a1*orthom00+a2*orthom01+a3*orthom02+ a1*orthom10+a2*orthom11+a3*orthom12;
        yy = y + a4*orthom20+a5*orthom21+a6*orthom22+ a4*orthom00+a5*orthom01+a6*orthom02+ a4*orthom10+a5*orthom11+a6*orthom12;
        zz = z + a7*orthom20+a8*orthom21+a9*orthom22+ a7*orthom00+a8*orthom01+a9*orthom02+ a7*orthom10+a8*orthom11+a9*orthom12;

	if ( GRA_VIEW == 3 )
		circf(xx+XOFFSET, yy+YOFFSET, 0.50);
	else if ( GRA_VIEW == 1 )
		circf(yy+XOFFSET, zz+YOFFSET, 0.50);
	else
		circf(zz+XOFFSET, xx+YOFFSET, 0.50);



	}


	}





        loadXfont(4711, "fixed");  
        font(4711);
        color(1);
        cmov2( -GRABOX/2.0,GRABOX/2.0-GRABOX*16.0/WINSIZE );
        charstr(framestring);


	if ( TRICK )
	{
	float	x, y, z, distance;

	if ( GRA_VIEW == 3 )
		move2(cCAs[realCAs[0]][0]+XOFFSET, cCAs[realCAs[0]][1]+YOFFSET);
	else if ( GRA_VIEW == 1 )
		move2(cCAs[realCAs[0]][1]+XOFFSET, cCAs[realCAs[0]][2]+YOFFSET);
	else
		move2(cCAs[realCAs[0]][2]+XOFFSET, cCAs[realCAs[0]][0]+YOFFSET);

	for ( i=1 ; i < realCAscount ; i++ )
	{
	if ( GRADIENT )
		color(colorindex[i*nofCAs/realCAscount]);
	else
		color(colorindex[realCAs[i]]);

	x = cCAs[realCAs[i]][0];
	y = cCAs[realCAs[i]][1];
	z = cCAs[realCAs[i]][2];

	distance = sqrt( (x-cCAs[realCAs[i-1]][0])*(x-cCAs[realCAs[i-1]][0]) + (y-cCAs[realCAs[i-1]][1])*(y-cCAs[realCAs[i-1]][1])
			 + (z-cCAs[realCAs[i-1]][2])*(z-cCAs[realCAs[i-1]][2]) );
		
	if ( distance > limitCAs[i] )
	{
	if ( GRA_VIEW == 3 )
		move2(x+XOFFSET, y+YOFFSET);
	else if ( GRA_VIEW == 1 )
		move2(y+XOFFSET, z+YOFFSET);
	else
		move2(z+XOFFSET, x+YOFFSET);
	}
	else
	{
	if ( GRA_VIEW == 3 )
		draw2(x+XOFFSET, y+YOFFSET);
	else if ( GRA_VIEW == 1 )
		draw2(y+XOFFSET, z+YOFFSET);
	else
		draw2(z+XOFFSET, x+YOFFSET);
	}

		}
	}


	if ( STEREO )
	{

	if ( GRA_VIEW == 3 )
		{
		viewport(302,600,1,600);
		ortho2( -GRABOX/4.0, GRABOX/4.0, -GRABOX/2.0, GRABOX/2.0);
		}
	else
		{
		viewport(1,299,1,600);
		ortho2( -GRABOX/4.0, GRABOX/4.0, -GRABOX/2.0, GRABOX/2.0);
		}


        color(1);
	linewidth( 1 );
	move2(-CROSS,0.0);
	draw2(CROSS,0.0);
	move2(0.0,-CROSS);
	draw2(0.0,CROSS);
	linewidth( LINEW );

	if ( GRA_VIEW == 3 )
	{
	aa1 = 0.994521895368273290;
	aa2 = 0.000000000000000000;
	aa3 =-0.104528463267653457;
	aa4 = 0.000000000000000000;
	aa5 = 1.000000000000000000;
	aa6 = 0.000000000000000000;
	aa7 = 0.104528463267653457;
	aa8 = 0.000000000000000000;
	aa9 = 0.994521895368273290;
	}
	else if ( GRA_VIEW == 1 )
	{
	aa1 = 0.994521895368273290;
	aa2 =-0.104528463267653457;
	aa3 = 0.000000000000000000;
	aa4 = 0.104528463267653457;
	aa5 = 0.994521895368273290;
	aa6 = 0.000000000000000000;
	aa7 = 0.000000000000000000;
	aa8 = 0.000000000000000000;
	aa9 = 1.000000000000000000;
	}
	else
	{
	aa1 = 1.000000000000000000;
	aa2 = 0.000000000000000000;
	aa3 = 0.000000000000000000;
	aa4 = 0.000000000000000000;
	aa5 = 0.994521895368273290;
	aa6 =-0.104528463267653457;
	aa7 = 0.000000000000000000;
	aa8 = 0.104528463267653457;
	aa9 = 0.994521895368273290;
	}

	for ( i=0 ; i < nofCAs ; i++ )
		{
			x = cCAs[i][0];
			y = cCAs[i][1];
			z = cCAs[i][2];
			ccCAs[i][0] = aa1*x + aa2*y + aa3*z;
			ccCAs[i][1] = aa4*x + aa5*y + aa6*z;
			ccCAs[i][2] = aa7*x + aa8*y + aa9*z;
		}




	for ( i=0 ; i < nofCAs ; i++ )
	{
	color(colorindex[i]);

	if ( GRA_VIEW == 3 )
		pnt2(ccCAs[i][0]+XOFFSET, ccCAs[i][1]+YOFFSET);
	else if ( GRA_VIEW == 1 )
		pnt2(ccCAs[i][1]+XOFFSET, ccCAs[i][2]+YOFFSET);
	else
		pnt2(ccCAs[i][2]+XOFFSET, ccCAs[i][0]+YOFFSET);

	}




	if ( PACKING )
	{
        for ( i=0 ; i < nofCAs ; i++ )
        {
        float   x, y, z;   
        float   xx, yy, zz;

	color(255);


	x = ccCAs[i][0];
	y = ccCAs[i][1];
	z = ccCAs[i][2];
	
        xx = x + a1*orthom00+a2*orthom01+a3*orthom02;
        yy = y + a4*orthom00+a5*orthom01+a6*orthom02;
        zz = z + a7*orthom00+a8*orthom01+a9*orthom02;

	if ( GRA_VIEW == 3 )
		pnt2(xx+XOFFSET, yy+YOFFSET);
	else if ( GRA_VIEW == 1 )
		pnt2(yy+XOFFSET, zz+YOFFSET);
	else
		pnt2(zz+XOFFSET, xx+YOFFSET);

        xx = x + a1*orthom10+a2*orthom11+a3*orthom12;
        yy = y + a4*orthom10+a5*orthom11+a6*orthom12;
        zz = z + a7*orthom10+a8*orthom11+a9*orthom12;

	if ( GRA_VIEW == 3 )
		pnt2(xx+XOFFSET, yy+YOFFSET);
	else if ( GRA_VIEW == 1 )
		pnt2(yy+XOFFSET, zz+YOFFSET);
	else
		pnt2(zz+XOFFSET, xx+YOFFSET);

        xx = x + a1*orthom20+a2*orthom21+a3*orthom22;
        yy = y + a4*orthom20+a5*orthom21+a6*orthom22;
        zz = z + a7*orthom20+a8*orthom21+a9*orthom22;

	if ( GRA_VIEW == 3 )
		pnt2(xx+XOFFSET, yy+YOFFSET);
	else if ( GRA_VIEW == 1 )
		pnt2(yy+XOFFSET, zz+YOFFSET);
	else
		pnt2(zz+XOFFSET, xx+YOFFSET);




        xx = x + a1*orthom00+a2*orthom01+a3*orthom02+ a1*orthom10+a2*orthom11+a3*orthom12;
        yy = y + a4*orthom00+a5*orthom01+a6*orthom02+ a4*orthom10+a5*orthom11+a6*orthom12;
        zz = z + a7*orthom00+a8*orthom01+a9*orthom02+ a7*orthom10+a8*orthom11+a9*orthom12;

	if ( GRA_VIEW == 3 )
		pnt2(xx+XOFFSET, yy+YOFFSET);
	else if ( GRA_VIEW == 1 )
		pnt2(yy+XOFFSET, zz+YOFFSET);
	else
		pnt2(zz+XOFFSET, xx+YOFFSET);

        xx = x + a1*orthom10+a2*orthom11+a3*orthom12+ a1*orthom20+a2*orthom21+a3*orthom22;
        yy = y + a4*orthom10+a5*orthom11+a6*orthom12+ a4*orthom20+a5*orthom21+a6*orthom22;
        zz = z + a7*orthom10+a8*orthom11+a9*orthom12+ a7*orthom20+a8*orthom21+a9*orthom22;

	if ( GRA_VIEW == 3 )
		pnt2(xx+XOFFSET, yy+YOFFSET);
	else if ( GRA_VIEW == 1 )
		pnt2(yy+XOFFSET, zz+YOFFSET);
	else
		pnt2(zz+XOFFSET, xx+YOFFSET);

        xx = x + a1*orthom20+a2*orthom21+a3*orthom22+ a1*orthom00+a2*orthom01+a3*orthom02;
        yy = y + a4*orthom20+a5*orthom21+a6*orthom22+ a4*orthom00+a5*orthom01+a6*orthom02;
        zz = z + a7*orthom20+a8*orthom21+a9*orthom22+ a7*orthom00+a8*orthom01+a9*orthom02;

	if ( GRA_VIEW == 3 )
		pnt2(xx+XOFFSET, yy+YOFFSET);
	else if ( GRA_VIEW == 1 )
		pnt2(yy+XOFFSET, zz+YOFFSET);
	else
		pnt2(zz+XOFFSET, xx+YOFFSET);


        xx = x + a1*orthom20+a2*orthom21+a3*orthom22+ a1*orthom00+a2*orthom01+a3*orthom02+ a1*orthom10+a2*orthom11+a3*orthom12;
        yy = y + a4*orthom20+a5*orthom21+a6*orthom22+ a4*orthom00+a5*orthom01+a6*orthom02+ a4*orthom10+a5*orthom11+a6*orthom12;
        zz = z + a7*orthom20+a8*orthom21+a9*orthom22+ a7*orthom00+a8*orthom01+a9*orthom02+ a7*orthom10+a8*orthom11+a9*orthom12;

	if ( GRA_VIEW == 3 )
		pnt2(xx+XOFFSET, yy+YOFFSET);
	else if ( GRA_VIEW == 1 )
		pnt2(yy+XOFFSET, zz+YOFFSET);
	else
		pnt2(zz+XOFFSET, xx+YOFFSET);

	}

	for ( i=0 ; i < realCAscount ; i++ )
	{
	float	x, y, z;
	float	xx, yy, zz;

	if ( GRADIENT )
		color(colorindex[i*nofCAs/realCAscount]);
	else
		color(colorindex[realCAs[i]]);

	x = ccCAs[realCAs[i]][0];
	y = ccCAs[realCAs[i]][1];
	z = ccCAs[realCAs[i]][2];
	
        xx = x + a1*orthom00+a2*orthom01+a3*orthom02;
        yy = y + a4*orthom00+a5*orthom01+a6*orthom02;
        zz = z + a7*orthom00+a8*orthom01+a9*orthom02;

	if ( GRA_VIEW == 3 )
		circf(xx+XOFFSET, yy+YOFFSET, 0.50);
	else if ( GRA_VIEW == 1 )
		circf(yy+XOFFSET, zz+YOFFSET, 0.50);
	else
		circf(zz+XOFFSET, xx+YOFFSET, 0.50);

        xx = x + a1*orthom10+a2*orthom11+a3*orthom12;
        yy = y + a4*orthom10+a5*orthom11+a6*orthom12;
        zz = z + a7*orthom10+a8*orthom11+a9*orthom12;

	if ( GRA_VIEW == 3 )
		circf(xx+XOFFSET, yy+YOFFSET, 0.50);
	else if ( GRA_VIEW == 1 )
		circf(yy+XOFFSET, zz+YOFFSET, 0.50);
	else
		circf(zz+XOFFSET, xx+YOFFSET, 0.50);

        xx = x + a1*orthom20+a2*orthom21+a3*orthom22;
        yy = y + a4*orthom20+a5*orthom21+a6*orthom22;
        zz = z + a7*orthom20+a8*orthom21+a9*orthom22;

	if ( GRA_VIEW == 3 )
		circf(xx+XOFFSET, yy+YOFFSET, 0.50);
	else if ( GRA_VIEW == 1 )
		circf(yy+XOFFSET, zz+YOFFSET, 0.50);
	else
		circf(zz+XOFFSET, xx+YOFFSET, 0.50);




        xx = x + a1*orthom00+a2*orthom01+a3*orthom02+ a1*orthom10+a2*orthom11+a3*orthom12;
        yy = y + a4*orthom00+a5*orthom01+a6*orthom02+ a4*orthom10+a5*orthom11+a6*orthom12;
        zz = z + a7*orthom00+a8*orthom01+a9*orthom02+ a7*orthom10+a8*orthom11+a9*orthom12;

	if ( GRA_VIEW == 3 )
		circf(xx+XOFFSET, yy+YOFFSET, 0.50);
	else if ( GRA_VIEW == 1 )
		circf(yy+XOFFSET, zz+YOFFSET, 0.50);
	else
		circf(zz+XOFFSET, xx+YOFFSET, 0.50);

        xx = x + a1*orthom10+a2*orthom11+a3*orthom12+ a1*orthom20+a2*orthom21+a3*orthom22;
        yy = y + a4*orthom10+a5*orthom11+a6*orthom12+ a4*orthom20+a5*orthom21+a6*orthom22;
        zz = z + a7*orthom10+a8*orthom11+a9*orthom12+ a7*orthom20+a8*orthom21+a9*orthom22;

	if ( GRA_VIEW == 3 )
		circf(xx+XOFFSET, yy+YOFFSET, 0.50);
	else if ( GRA_VIEW == 1 )
		circf(yy+XOFFSET, zz+YOFFSET, 0.50);
	else
		circf(zz+XOFFSET, xx+YOFFSET, 0.50);

        xx = x + a1*orthom20+a2*orthom21+a3*orthom22+ a1*orthom00+a2*orthom01+a3*orthom02;
        yy = y + a4*orthom20+a5*orthom21+a6*orthom22+ a4*orthom00+a5*orthom01+a6*orthom02;
        zz = z + a7*orthom20+a8*orthom21+a9*orthom22+ a7*orthom00+a8*orthom01+a9*orthom02;

	if ( GRA_VIEW == 3 )
		circf(xx+XOFFSET, yy+YOFFSET, 0.50);
	else if ( GRA_VIEW == 1 )
		circf(yy+XOFFSET, zz+YOFFSET, 0.50);
	else
		circf(zz+XOFFSET, xx+YOFFSET, 0.50);


        xx = x + a1*orthom20+a2*orthom21+a3*orthom22+ a1*orthom00+a2*orthom01+a3*orthom02+ a1*orthom10+a2*orthom11+a3*orthom12;
        yy = y + a4*orthom20+a5*orthom21+a6*orthom22+ a4*orthom00+a5*orthom01+a6*orthom02+ a4*orthom10+a5*orthom11+a6*orthom12;
        zz = z + a7*orthom20+a8*orthom21+a9*orthom22+ a7*orthom00+a8*orthom01+a9*orthom02+ a7*orthom10+a8*orthom11+a9*orthom12;

	if ( GRA_VIEW == 3 )
		circf(xx+XOFFSET, yy+YOFFSET, 0.50);
	else if ( GRA_VIEW == 1 )
		circf(yy+XOFFSET, zz+YOFFSET, 0.50);
	else
		circf(zz+XOFFSET, xx+YOFFSET, 0.50);



	}


	}







        loadXfont(4711, "fixed");  
        font(4711);
        color(1);
        cmov2( -GRABOX/2.0,GRABOX/2.0-GRABOX*16.0/WINSIZE );
        charstr(framestring);


	if ( TRICK )
	{
	float	x, y, z, distance;

	if ( GRA_VIEW == 3 )
		move2(ccCAs[realCAs[0]][0]+XOFFSET, ccCAs[realCAs[0]][1]+YOFFSET);
	else if ( GRA_VIEW == 1 )
		move2(ccCAs[realCAs[0]][1]+XOFFSET, ccCAs[realCAs[0]][2]+YOFFSET);
	else
		move2(ccCAs[realCAs[0]][2]+XOFFSET, ccCAs[realCAs[0]][0]+YOFFSET);

	for ( i=1 ; i < realCAscount ; i++ )
	{
	if ( GRADIENT )
		color(colorindex[i*nofCAs/realCAscount]);
	else
		color(colorindex[realCAs[i]]);

	x = ccCAs[realCAs[i]][0];
	y = ccCAs[realCAs[i]][1];
	z = ccCAs[realCAs[i]][2];

	distance = sqrt( (x-ccCAs[realCAs[i-1]][0])*(x-ccCAs[realCAs[i-1]][0]) + (y-ccCAs[realCAs[i-1]][1])*(y-ccCAs[realCAs[i-1]][1])
			 + (z-ccCAs[realCAs[i-1]][2])*(z-ccCAs[realCAs[i-1]][2]) );
		
	if ( distance > limitCAs[i] )
	{
	if ( GRA_VIEW == 3 )
		move2(x+XOFFSET, y+YOFFSET);
	else if ( GRA_VIEW == 1 )
		move2(y+XOFFSET, z+YOFFSET);
	else
		move2(z+XOFFSET, x+YOFFSET);
	}
	else
	{
	if ( GRA_VIEW == 3 )
		draw2(x+XOFFSET, y+YOFFSET);
	else if ( GRA_VIEW == 1 )
		draw2(y+XOFFSET, z+YOFFSET);
	else
		draw2(z+XOFFSET, x+YOFFSET);
	}

		}
	}

	}





	reshapeviewport();
	ortho2( -GRABOX/2.0, GRABOX/2.0, -GRABOX/2.0, GRABOX/2.0);

	
	gflush();
	swapbuffers();
	color(0);
	clear();
	linewidth( 1 );
	if ( ! STEREO )
	{
        color(1);
	move2(-CROSS,0.0);
	draw2(CROSS,0.0);
	move2(0.0,-CROSS);
	draw2(0.0,CROSS);
	}
        color(255);
	for ( i=0 ; i < GRABOX/2.0 ; i += 5)
		{
			move2(i, -GRABOX/2.0);
			draw2(i, -GRABOX/2.0+CROSS);
			move2(i, GRABOX/2.0);
			draw2(i, GRABOX/2.0-CROSS);
				}
	for ( i=-5 ; i > -GRABOX/2.0 ; i -= 5)
		{
			move2(i, -GRABOX/2.0);
			draw2(i, -GRABOX/2.0+CROSS);
			move2(i, GRABOX/2.0);
			draw2(i, GRABOX/2.0-CROSS);
				}
	for ( i=0 ; i < GRABOX/2.0 ; i += 5)
		{
			move2(-GRABOX/2.0,i);
			draw2(-GRABOX/2.0+CROSS,i);
			move2(GRABOX/2.0,i);
			draw2(GRABOX/2.0-CROSS,i);
				}
	for ( i=-5 ; i > -GRABOX/2.0 ; i -= 5)
		{
			move2(-GRABOX/2.0,i);
			draw2(-GRABOX/2.0+CROSS,i);
			move2(GRABOX/2.0,i);
			draw2(GRABOX/2.0-CROSS,i);
				}
	linewidth( LINEW );

	return;

}


void copyCAs()
{
	int	i;

	omega = 0.0;
	phi = 0.0;
	kappa = 0.0;
	for ( i=0 ; i < nofCAs ; i++ )
		{
			cCAs[i][0] = CAs[i][0];
			cCAs[i][1] = CAs[i][1];
			cCAs[i][2] = CAs[i][2];
		}

	dkappa = getrand * M_PI / 90.0;
	domega = getrand * M_PI / 90.0;
	dphi = getrand * M_PI/ 90.0;
	now_playing = NO;
}


void calc_ortho()
{
	double V;
	double alpha, beta, gamma;

	alpha = M_PI * cell_alpha / 180.0;
	beta  = M_PI * cell_beta  / 180.0;
	gamma = M_PI * cell_gamma / 180.0;

/*
	printf("%15.8f %15.8f %15.8f %15.8f %15.8f %15.8f \n", cell_a, cell_b, cell_c, cell_alpha, cell_beta, cell_gamma );
*/

        V = cell_a*cell_b*cell_c* sqrt( 1.0 - cos(alpha)*cos(alpha)- cos(beta)*cos(beta) - 
		cos(gamma)*cos(gamma) + 2.0*(cos(alpha)*cos(beta)*cos(gamma)));
                                                                        
        orthom00 =  V / (cell_c*cell_b * sin(alpha) ); 
        orthom10 = 0.0;
        orthom20 = 0.0;
        orthom01 = cell_a * ( cos(gamma) - cos(beta)*cos(alpha)) / sin(alpha);
        orthom11 = cell_b * sin(alpha);
        orthom21 = 0.0 ;
        orthom02 = cell_a * cos(beta);
        orthom12 = cell_b * cos(alpha);
        orthom22 = cell_c;

/*
	printf("%15.8f %15.8f %15.8f %15.8f %15.8f %15.8f %15.8f %15.8f %15.8f        %15.8f\n", 
		orthom[0][0], orthom[0][1], orthom[0][2], orthom[1][0], orthom[1][1], 
		orthom[1][2], orthom[2][0], orthom[2][1], orthom[2][2], V );
*/

}


#endif


/* torsion calculation stolen from RDPARM/PTRAJ */

double torsion(	double x1, double y1, double z1,
		double x2, double y2, double z2,
		double x3, double y3, double z3,
		double x4, double y4, double z4)
{
  double Lx, Ly, Lz, Lnorm;
  double Rx, Ry, Rz, Rnorm;
  double Sx, Sy, Sz;
  double angle;

  VOP_3D_COORDS_CROSS_PRODUCT(     Lx,      Ly,      Lz,
			      (x2-x1), (y2-y1), (z2-z1),
			      (x3-x2), (y3-y2), (z3-z2));

  VOP_3D_COORDS_CROSS_PRODUCT(     Rx,      Ry,      Rz,
			      (x4-x3), (y4-y3), (z4-z3),
			      (x2-x3), (y2-y3), (z2-z3));

  Lnorm = sqrt(Lx*Lx + Ly*Ly + Lz*Lz);
  Rnorm = sqrt(Rx*Rx + Ry*Ry + Rz*Rz);

  VOP_3D_COORDS_CROSS_PRODUCT(Sx, Sy, Sz,
			      Lx, Ly, Lz,
			      Rx, Ry, Rz);

  angle = (Lx*Rx + Ly*Ry + Lz*Rz) / (Lnorm * Rnorm);

  if ( angle > 1.0 ) angle = 1.0;
  if ( angle < -1.0 ) angle = -1.0;

  angle = acos( angle );
  angle = 180.0 * angle / M_PI;

  if ( (Sx * (x3-x2) + Sy * (y3-y2) + Sz * (z3-z2)) < 0 )
    angle = -angle;
  return(angle);
}



/* bending angle calculation adapted from torsion (above) */

double bendangle( double x1, double y1, double z1,
        double x2, double y2, double z2,
        double x3, double y3, double z3)
{
  double Lx, Ly, Lz, Lnorm;
  double Rx, Ry, Rz, Rnorm;
  double angle;

  Lx = x2-x1;
  Ly = y2-y1;
  Lz = z2-z1;
  Rx = x2-x3;
  Ry = y2-y3;
  Rz = z2-z3;
  Lnorm = sqrt(Lx*Lx + Ly*Ly + Lz*Lz);
  Rnorm = sqrt(Rx*Rx + Ry*Ry + Rz*Rz);

  angle = (Lx*Rx + Ly*Ry + Lz*Rz) / (Lnorm * Rnorm);

  if ( angle > 1.0 ) angle = 1.0;
  if ( angle < -1.0 ) angle = -1.0;

  angle = acos( angle );
  angle = 180.0 * angle / M_PI;

  if ( angle < 0 )
    angle = -angle;

  return(angle);
}













/*****************************************************************************************************************************/
/**	Build a list of torsion angles for dPCA									 	    **/
/*****************************************************************************************************************************/

int	build_torsions()
{
	int	tot_torsions = 0;
	int	i;	

	
	if ( nofCAs % 3 != 0 )
		{
			printf("\033[31m\033[1mNumber of N,C,CA atoms not a multiple of three ? Abort.\033[0m\n");
			myexit( 1 );
					}
	if ( nofCAs < 6 )
		{
			printf("\033[31m\033[1mToo few N,C,CA atoms ? Abort.\033[0m\n");
			myexit( 1 );
					}


						/* Sanity check on atoms selected for dPCA */
	for ( i=0 ; i < nofCAs ; i++ )
		{
			if ( 	strncmp( &backbone  [i][5], " N   ", 5) != 0	&&
				strncmp( &backbone  [i][5], " CA  ", 5) != 0    &&
				strncmp( &backbone  [i][5], " C   ", 5) != 0	)
					{
					printf("\033[31m\033[1mUnexpected atom for dPCA : %s\033[0m\n" ,&backbone[i][5] );
					myexit( 1 );
					}
				
		}


								/* For every N,CA,C triplet */
	for ( i=0 ; i < nofCAs ; i += 3 )
	{
								/* While the next triplet belongs to the next residue, do ... */
		while( str_resid[i+3] == str_resid[i]+1 )
		{
			int	N1=0, CA1=0, C1=0;
			int	N2=0, CA2=0, C2=0;
			
											/* Find and assign N, CA, C for */
											/* current and next residue 	*/
			if ( strncmp( &backbone  [i][5], " N   ", 5) == 0 )
				N1 = i;
			else
				if ( strncmp( &backbone  [i][5], " CA  ", 5) == 0 )
					CA1 = i;
			else    
				if ( strncmp( &backbone  [i][5], " C   ", 5) == 0 )
					C1 = i;
			if ( strncmp( &backbone  [i+1][5], " N   ", 5) == 0 )
				N1 = i+1;
			else
				if ( strncmp( &backbone  [i+1][5], " CA  ", 5) == 0 )
					CA1 = i+1;
			else    
				if ( strncmp( &backbone  [i+1][5], " C   ", 5) == 0 )
					C1 = i+1;
			if ( strncmp( &backbone  [i+2][5], " N   ", 5) == 0 )
				N1 = i+2;
			else
				if ( strncmp( &backbone  [i+2][5], " CA  ", 5) == 0 )
					CA1 = i+2;
			else    
				if ( strncmp( &backbone  [i+2][5], " C   ", 5) == 0 )
					C1 = i+2;

			if ( strncmp( &backbone  [i+3][5], " N   ", 5) == 0 )
				N2 = i+3;
			else
				if ( strncmp( &backbone  [i+3][5], " CA  ", 5) == 0 )
					CA2 = i+3;
			else    
				if ( strncmp( &backbone  [i+3][5], " C   ", 5) == 0 )
					C2 = i+3;
			if ( strncmp( &backbone  [i+4][5], " N   ", 5) == 0 )
				N2 = i+4;
			else
				if ( strncmp( &backbone  [i+4][5], " CA  ", 5) == 0 )
					CA2 = i+4;
			else    
				if ( strncmp( &backbone  [i+4][5], " C   ", 5) == 0 )
					C2 = i+4;
			if ( strncmp( &backbone  [i+5][5], " N   ", 5) == 0 )
				N2 = i+5;
			else
				if ( strncmp( &backbone  [i+5][5], " CA  ", 5) == 0 )
					CA2 = i+5;
			else    
				if ( strncmp( &backbone  [i+5][5], " C   ", 5) == 0 )
					C2 = i+5;
			                                                                        
				
			tetraplets[ tot_torsions][0] = N1;
			tetraplets[ tot_torsions][1] = CA1;
			tetraplets[ tot_torsions][2] = C1;
			tetraplets[ tot_torsions][3] = N2;
			tot_torsions++;
			tetraplets[ tot_torsions][0] = C1;
			tetraplets[ tot_torsions][1] = N2;
			tetraplets[ tot_torsions][2] = CA2;
			tetraplets[ tot_torsions][3] = C2;
			tot_torsions++;
			
			i += 3;	
		}

		if ( i < nofCAs -  3 )
			{
				if ( VERBOSE )
					printf("\033[33mBreak in chain detected during torsion preparation. Skipping ...\033[0m\n");

				i += 3;
			}
	}

	if ( VERBOSE )
	printf("\033[33mStarting dPCA with %d torsion angles\033[0m\n", tot_torsions);


	return( tot_torsions );



}








/*****************************************************************************************************************************/
/**	Build a list of torsion angles for dPCA including CHI1s							 	    **/
/*****************************************************************************************************************************/

int	build_torsions_with_chi()
{
	int	tot_torsions = 0;
	int	i, k;	
	char    back[MAX_NOF_BACK][11];
	int	index_back[MAX_NOF_BACK];
	int	index_side[MAX_NOF_BACK];
	int	nof_back;
	int	nof_side;
	int	tot_back = 0;
	int 	tot_side = 0;	
	
	
	if ( nofCAs < 6 )
		{
			printf("\033[31m\033[1mToo few atoms selected for dPCA ? Abort.\033[0m\n");
			myexit( 1 );
					}




	/************************************************************************************************/
	/* This is ugly. Separate the backbone dihedrals from chi1's. Process the backbone as usually, 	*/
	/* then process side chains 									*/
	/************************************************************************************************/


						/* Isolate backbone atoms. Keep the correspondence with backbone[] */	
	nof_back = 0;
	for ( i=0 ; i < nofCAs ; i++ )
		{
			if ( 	strncmp( &backbone  [i][5], " N   ", 5) == 0	||
				strncmp( &backbone  [i][5], " CA  ", 5) == 0    ||
				strncmp( &backbone  [i][5], " C   ", 5) == 0	)
					{
						strcpy( back[ nof_back ], backbone[i] );
						index_back[ nof_back ] = i;
						nof_back++;
					}
		}



						/* Isolate SIDECHAIN atoms. Keep the correspondence with backbone[] 	*/
						/* Try to exclude ALAs and GLYs at this stage (bound to fail)		*/
	nof_side = 0;
	for ( i=0 ; i < nofCAs-3 ; i++ )
		{
			if ( 	strncmp( &backbone  [ i   ][5], " N   ", 5) == 0    &&
				strncmp( &backbone  [ i+1 ][5], " CA  ", 5) == 0    &&
				strncmp( &backbone  [ i+2 ][5], " CB  ", 5) == 0    &&
				( strncmp( &backbone  [ i+3 ][5], " N   ", 5) != 0  &&
				  strncmp( &backbone  [ i+3 ][5], " CA  ", 5) != 0  &&
				  strncmp( &backbone  [ i+3 ][5], " C   ", 5) != 0  ) )
					{
/*						printf("%d %s\n", str_resid[ i ], backbone  [ i ] );
						printf("%d %s\n", str_resid[ i+1 ], backbone  [ i+1 ] );
						printf("%d %s\n", str_resid[ i+2 ], backbone  [ i+2 ] );
						printf("%d %s\n", str_resid[ i+3 ], backbone  [ i+3 ] );
*/						
						index_side[ nof_side ] = i;
						nof_side++;
						i++;
						
						index_side[ nof_side ] = i;
						nof_side++;
						i++;
						
						index_side[ nof_side ] = i;
						nof_side++;
						i++;
						
						index_side[ nof_side ] = i;
						nof_side++;
						i++;
						
					}
		}
	

/*
	printf("\n\n");
	for ( i=0 ; i < nof_back ; i++ )
		printf("%d %s \n", str_resid[ index_back[i] ], back[i] );

	printf("\n\n");
	for ( i=0 ; i < nof_side ; i++ )
		printf("%d %s \n", str_resid[ index_side[i] ], side[i] );

	exit(1);
*/


								/* For every N,CA,C triplet */
	for ( i=0 ; i < nof_back ; i += 3 )
	{
								/* While the next triplet belongs to the next residue, do ... */
		while( str_resid[ index_back[i+3] ] == str_resid[ index_back[i] ]+1 )
		{
			int	N1=0, CA1=0, C1=0;
			int	N2=0, CA2=0, C2=0;
			
											/* Find and assign N, CA, C for */
											/* current and next residue 	*/
			if ( strncmp( &back  [i][5], " N   ", 5) == 0 )
				N1 = index_back[i];
			else
				if ( strncmp( &back  [i][5], " CA  ", 5) == 0 )
					CA1 = index_back[i];
			else    
				if ( strncmp( &back  [i][5], " C   ", 5) == 0 )
					C1 = index_back[i];
			if ( strncmp( &back  [i+1][5], " N   ", 5) == 0 )
				N1 = index_back[i+1];
			else
				if ( strncmp( &back  [i+1][5], " CA  ", 5) == 0 )
					CA1 = index_back[i+1];
			else    
				if ( strncmp( &back  [i+1][5], " C   ", 5) == 0 )
					C1 = index_back[i+1];
			if ( strncmp( &back  [i+2][5], " N   ", 5) == 0 )
				N1 = index_back[i+2];
			else
				if ( strncmp( &back  [i+2][5], " CA  ", 5) == 0 )
					CA1 = index_back[i+2];
			else    
				if ( strncmp( &back  [i+2][5], " C   ", 5) == 0 )
					C1 = index_back[i+2];

			if ( strncmp( &back  [i+3][5], " N   ", 5) == 0 )
				N2 = index_back[i+3];
			else
				if ( strncmp( &back  [i+3][5], " CA  ", 5) == 0 )
					CA2 = index_back[i+3];
			else    
				if ( strncmp( &back  [i+3][5], " C   ", 5) == 0 )
					C2 = index_back[i+3];
			if ( strncmp( &back  [i+4][5], " N   ", 5) == 0 )
				N2 = index_back[i+4];
			else
				if ( strncmp( &back  [i+4][5], " CA  ", 5) == 0 )
					CA2 = index_back[i+4];
			else    
				if ( strncmp( &back  [i+4][5], " C   ", 5) == 0 )
					C2 = index_back[i+4];
			if ( strncmp( &back  [i+5][5], " N   ", 5) == 0 )
				N2 = index_back[i+5];
			else
				if ( strncmp( &back  [i+5][5], " CA  ", 5) == 0 )
					CA2 = index_back[i+5];
			else    
				if ( strncmp( &back  [i+5][5], " C   ", 5) == 0 )
					C2 = index_back[i+5];

			tetraplets[ tot_torsions][0] = N1;
			tetraplets[ tot_torsions][1] = CA1;
			tetraplets[ tot_torsions][2] = C1;
			tetraplets[ tot_torsions][3] = N2;
			tot_torsions++;
			tetraplets[ tot_torsions][0] = C1;
			tetraplets[ tot_torsions][1] = N2;
			tetraplets[ tot_torsions][2] = CA2;
			tetraplets[ tot_torsions][3] = C2;
			tot_torsions++;
			tot_back += 2;
			
			/* Add Chi1 torsion if present */
			for ( k=0 ; k < nof_side-3 ; k++ )
				{
					if ( index_side[k] == N1 && index_side[k+1] == CA1 )
						{
						tetraplets[ tot_torsions][0] = index_side[ k ];
						tetraplets[ tot_torsions][1] = index_side[ k +1];
						tetraplets[ tot_torsions][2] = index_side[ k +2];
						tetraplets[ tot_torsions][3] = index_side[ k +3];
						tot_torsions++;
						tot_side++;
						break;
						}
					else if ( index_side[k] == N2 && index_side[k+1] == CA2 )
						{
						tetraplets[ tot_torsions][0] = index_side[ k ];
						tetraplets[ tot_torsions][1] = index_side[ k +1];
						tetraplets[ tot_torsions][2] = index_side[ k +2];
						tetraplets[ tot_torsions][3] = index_side[ k +3];
						tot_torsions++;
						tot_side++;
						break;
						}
					
				}			
			
			
			i += 3;	
		}

		if ( i < nof_back -  3 )
			{
				if ( VERBOSE )
					printf("\033[33mBreak in chain detected during torsion preparation. Skipping ...\033[0m\n");

				i += 3;
			}
	}


	if ( VERBOSE )
		{
		printf("\033[33mStarting dPCA with %d torsion angles\033[0m\n", tot_torsions);
		printf("\033[33mof which %d are backbone and %d are chi1 angles.\033[0m\n", tot_back, tot_side );
		}


	return( tot_torsions );



}









void 	cluster( int bins, int frames, float limit )
{
	int	i, k, m;
	FILE	*clusters;
	float	***inter;
	float	***original;
	float	aver, rmsd;
	float	val;
	int	nof_points;
	float	current_max;
	int	current_peak;
	int	maxx, maxy, maxz ;
	float	val1, val2, val3;
	int	pos1, pos2, pos3;
	float	cutoff;
	double	shannon;
	static int	populations[10000];		/* Bloody windoze need 'static' with -fstack-check */
	
	
/*
	float	start;
*/

	if ( VERBOSE )
		{
		printf("Starting cluster analysis on three principal components.\n");
		printf("Matrix of principal components distribution is %dx%dx%d.\n", bins, bins, bins);
		}


	clusters = fopen( "carma.clusters.dat", "w");
	if ( clusters == NULL )
		{	
			printf("\033[31m\033[1mCan not open output file. Abort.\033[0m\n");
			myexit(1);
					}
	

	if ( SHANNON == YES )
	{
	/* Shannon entropy of distribution */
	aver = 0.0;
	for ( i=1 ; i <= bins ; i++ )	
	for ( k=1 ; k <= bins ; k++ )	
	for ( m=1 ; m <= bins ; m++ )	
		aver += CLUSTER[i][k][m];
			
	shannon = 0.0;
	for ( i=1 ; i <= bins ; i++ )	
	for ( k=1 ; k <= bins ; k++ )	
	for ( m=1 ; m <= bins ; m++ )	
		if ( (val=CLUSTER[i][k][m]) > 0.50 )
			{
				shannon += -val*( log((double)(val)) - log((double)(aver)) ) / (double)(aver);
			}

	printf("Configurational entropy of PC distribution is %f\n", shannon );

	}

	if ( VERBOSE )
		printf("Smoothing data matrix ...\n");


	/* Take logarithm first ... */
/*	for ( i=1 ; i <= bins ; i++ )	
	for ( k=1 ; k <= bins ; k++ )	
	for ( m=1 ; m <= bins ; m++ )	
		if ( (val=CLUSTER[i][k][m]) < 0.50 )
			CLUSTER[i][k][m] = log( 0.50 );
		else
			CLUSTER[i][k][m] = log( val );
*/


	/* ... then smooth the matrix */
	inter = f3tensor( 1, bins, 1, bins, 1, bins );
	original = f3tensor( 1, bins, 1, bins, 1, bins );

	for ( i=1 ; i <= bins ; i++ )	
	for ( k=1 ; k <= bins ; k++ )	
	for ( m=1 ; m <= bins ; m++ )	
		inter[i][k][m] = 0;

	for ( i=2 ; i < bins ; i++ )	
	for ( k=2 ; k < bins ; k++ )	
	for ( m=2 ; m < bins ; m++ )	
		{
			val = ( CLUSTER[i][k][m]	+CLUSTER[i][k][m+1]	+CLUSTER[i][k][m-1]+
				CLUSTER[i][k+1][m]	+CLUSTER[i][k+1][m+1]	+CLUSTER[i][k+1][m-1]+
				CLUSTER[i][k-1][m]	+CLUSTER[i][k-1][m+1]	+CLUSTER[i][k-1][m-1]+
				CLUSTER[i+1][k][m]	+CLUSTER[i+1][k][m+1]	+CLUSTER[i+1][k][m-1]+
                                CLUSTER[i+1][k+1][m]	+CLUSTER[i+1][k+1][m+1]	+CLUSTER[i+1][k+1][m-1]+
                                CLUSTER[i+1][k-1][m]	+CLUSTER[i+1][k-1][m+1]	+CLUSTER[i+1][k-1][m-1]+
				CLUSTER[i-1][k][m]	+CLUSTER[i-1][k][m+1]	+CLUSTER[i-1][k][m-1]+
                                CLUSTER[i-1][k+1][m]	+CLUSTER[i-1][k+1][m+1]	+CLUSTER[i-1][k+1][m-1]+
                                CLUSTER[i-1][k-1][m]	+CLUSTER[i-1][k-1][m+1]	+CLUSTER[i-1][k-1][m-1]   ) / 27.0;

			inter[i][k][m] = val;

		}

	for ( i=1 ; i <= bins ; i++ )	
	for ( k=1 ; k <= bins ; k++ )	
	for ( m=1 ; m <= bins ; m++ )	
		{
			CLUSTER[i][k][m] = inter[i][k][m];
			original[i][k][m] = inter[i][k][m];
		}




							/* Write 3D map */
	if ( MAKE_3D == YES )
		{
			int     iuvw[3];
			float	cell[6];
			char	filename[300];
			int	new_bins;
			int	ii, kk, mm;
			float	max, mapaver, mapsigma;
			float   *pmap;
			int	gx, gy, gz;
			FILE	*cns;
			
			if (VERBOSE)
				printf("Writing-out 3D PCA maps ...\n");
			
			if ( bins > 128 )
			{
										/* Reduce map size to 128x128x128 if big */
			free_f3tensor( inter, 1, bins, 1, bins, 1, bins );
			new_bins = 128;
			inter = f3tensor( 1, new_bins, 1, new_bins, 1, new_bins );

			for ( ii=0 ; ii < new_bins ; ii++ )	
			for ( kk=0 ; kk < new_bins ; kk++ )	
			for ( mm=0 ; mm < new_bins ; mm++ )	
				{
					int	dg, dx, dy, dz;
					float	sum;
					
					i = (int)( (float)(bins)/(float)(new_bins) * ii + 0.5) + 1;
					k = (int)( (float)(bins)/(float)(new_bins) * kk + 0.5) + 1;
					m = (int)( (float)(bins)/(float)(new_bins) * mm + 0.5) + 1;
					dg = (int)( (float)(bins)/(float)(2.0 * new_bins) + 0.5 );
					
					sum = 0.0;
					for ( dx = i - dg ; dx <= i + dg ; dx++ )
					for ( dy = k - dg ; dy <= k + dg ; dy++ )
					for ( dz = m - dg ; dz <= m + dg ; dz++ )
						if ( 	dx >= 1 && dy >= 1 && dz >= 1 &&
							dx <= bins && dy <= bins && dz <= bins )
							sum += CLUSTER[dx][dy][dz];
					
					inter[ii+1][kk+1][mm+1] = sum;		
				
				}

			}
			else
				new_bins = bins;


			pmap = &inter[1][1][1];
			
			max = 0.0;
			mapaver = 0.0;
			mapsigma = 0.0;
			for ( i=0 ; i < new_bins*new_bins*new_bins ; i++ )
				{
					if ( pmap[i] > max )
						max =  pmap[i];
					mapaver += pmap[i];
								}
									
			mapaver /= (float)(new_bins*new_bins*new_bins);
			for ( i=0 ; i < new_bins*new_bins*new_bins ; i++ )
				mapsigma += (pmap[i]-mapaver)*(pmap[i]-mapaver);

			mapsigma = sqrt( mapsigma / (float)(new_bins*new_bins*new_bins));


			if ( VERBOSE )
				{
					printf("Maximum count recorded is %f\n", max );
					printf("Map average and sigma are %f and %f\n", mapaver, mapsigma );
				}
		

			sprintf( filename, "carma.3d_landscape.cns" );
							
			cns = fopen( filename, "w");
		        if ( cns == NULL )
		                {
		                printf("\033[31m\033[1mCan not open map file for writing. Abort.\n");
		                myexit(1);
		                }

			fprintf(cns, "\n");
			fprintf(cns, "       2\n");
			fprintf(cns, " REMARKS FILENAME=\"%s\"\n", filename);
			fprintf(cns, " REMARKS 3D PCA-derived landscape, created by Carma v.1.2\n");
			
			fprintf(cns, "%7d %7d %7d %7d %7d %7d %7d %7d %7d\n", new_bins, 0, new_bins-1, new_bins, 0, new_bins-1,new_bins, 0, new_bins-1 );
			fprintf(cns, "%7.5E %7.5E %7.5E %7.5E %7.5E %7.5E\n", 2.0*limit, 2.0*limit, 2.0*limit, 90.00, 90.00, 90.00 );
			fprintf(cns, "ZYX\n");
			for (gz=1 ; gz <= new_bins ; gz ++)
			{
			i = 0;
			fprintf(cns, "%8d\n", gz-1 );
			for (gy=1 ; gy <= new_bins ; gy ++)
			for (gx=1 ; gx <= new_bins ; gx ++)
				{
					fprintf(cns, "%+8.5E", inter[gx][gy][gz] );
					i++;
					if ( i == 6 )
						{
							i = 0;
							fprintf(cns, "\n");
						}
				}

			if ( i != 0 )
				fprintf(cns, "\n");

			}
			
			fprintf(cns, "   -9999\n");
				
			fprintf(cns, "%12.4E%12.4E\n", mapaver, mapsigma );

			fclose(cns);


			
			iuvw[0] = 3;
			iuvw[1] = 2;
			iuvw[2] = 1;
			cell[0] = 2.0*limit;
			cell[1] = 2.0*limit;
			cell[2] = 2.0*limit;
			cell[3] = 90.0;
			cell[4] = 90.0;
			cell[5] = 90.0;
			
			sprintf( filename, "carma.3d_landscape.na4" );
				
			write_map( &filename[0], inter, new_bins, new_bins, new_bins, iuvw, 2, "Produced from carma v.1.2", cell );
			
		}
	
	




	/* Find average */
	aver = 0.0;
	nof_points = 0;
	current_max = -1.0;
	for ( i=1 ; i <= bins ; i++ )	
	for ( k=1 ; k <= bins ; k++ )	
	for ( m=1 ; m <= bins ; m++ )	
		if ( (val=CLUSTER[i][k][m]) > 0.50 ) 
			{
				aver += val;
				nof_points++;
				if ( val > current_max )
					current_max = val;
			}
	
	if ( current_max > 999998.0 )
		{
			printf("\033[31m\033[1m\n\nMore than 1 million frames on a single map point ? Abort.\033[0m\n");
			exit( 1 );
		}

	aver /= (nof_points);
	GRID_POINTS = nof_points;
	MAP_AVER = aver;

	/* Find rmsd */
	rmsd = 0.0;
	for ( i=1 ; i <= bins ; i++ )	
	for ( k=1 ; k <= bins ; k++ )	
	for ( m=1 ; m <= bins ; m++ )	
		if ( (val=CLUSTER[i][k][m]) > 0.50 ) 
			{
				rmsd += (val - aver)*(val - aver);
			}

	rmsd = sqrt( rmsd / nof_points );
	MAP_RMSD = rmsd;



	if ( VERBOSE )
		printf("Locating clusters ...\n");





	/* RMSD cutoff defined by user ... */
	
	if ( CLU_RMS > 0.0 )
	{
	cutoff = aver + CLU_RMS * rmsd;

	maxx = 0;
	maxy = 0;
	maxz = 0;
	current_peak = 1;
	while ( 1 )
	{

	current_max = -1.0;
	for ( i=1 ; i <= bins ; i++ )	
	for ( k=1 ; k <= bins ; k++ )	
	for ( m=1 ; m <= bins ; m++ )	
		if ( (val=CLUSTER[i][k][m]) > current_max && val < 999999.0 ) 
			{
				current_max = val;
				maxx = i;
				maxy = k;
				maxz = m;
			}

	if ( current_max < cutoff )
		break;

	erase_peak( cutoff, maxx, maxy, maxz, current_max, 1000000.0+current_peak, bins);
	current_peak++;
	}

	current_peak--;

	if (VERBOSE)
		printf("Number of clusters %d\n", current_peak );



	}
	else               /* Determine RMSD cutoff automatically ... */
	{

	double	testing;	
	int	max_clust;
	int	nof_cl[201];
	float	var_expl[201];
	FILE	*out;
	static	float	variances[2000][2];		/* Bloody windoze need 'static' with -fstack-check */
	static	float	differences[2000][2];
	
	
	if (VERBOSE)
		printf("Testing cutoffs : %8.2f", 20.0 );


	for ( i=0 ; i < 201 ; i++ )
		nof_cl[i] = 0;
										/* For all these rmsd cutoffs, calculate variance explained */
	for ( testing = 20.0l ; testing >= 0.099999l ; testing -= 0.10l )
	{
		
		if ( VERBOSE )
			printf("%8.2f", testing );

		for ( i=1 ; i <= bins ; i++ )	
		for ( k=1 ; k <= bins ; k++ )	
		for ( m=1 ; m <= bins ; m++ )	
			CLUSTER[i][k][m] = original[i][k][m];

		cutoff = aver + testing * rmsd;
		
		maxx = 0;
		maxy = 0;
		maxz = 0;
		current_peak = 1;


		MAP_VARIANCE = 0.0;
		
		while ( 1 )
		{
		
		current_max = -1.0;
		for ( i=1 ; i <= bins ; i++ )	
		for ( k=1 ; k <= bins ; k++ )	
		for ( m=1 ; m <= bins ; m++ )	
			if ( (val=CLUSTER[i][k][m]) > current_max && val < 999999.0 ) 
				{
					current_max = val;
					maxx = i;
					maxy = k;
					maxz = m;
				}

		if ( current_max < cutoff )
			break;

		erase_peak( cutoff, maxx, maxy, maxz, current_max, 1000000.0+current_peak, bins);
		current_peak++;
		}

		current_peak--;

		nof_cl[ (int)( testing / 0.10 + 0.50 ) ] = current_peak;
	
		var_expl[ (int)( testing / 0.10 + 0.50 ) ] = MAP_VARIANCE / ( GRID_POINTS * MAP_RMSD * MAP_RMSD);
		
	
	}


	if ( VERBOSE )
		printf("Done ...    \n");




	/* What is the max number of clusters observed ? */
	max_clust = nof_cl[ 10 ];
	for ( i=10 ; i <= 200 ; i++ )
		if ( nof_cl[ i ] >= max_clust )
			max_clust = nof_cl[ i ];


	/* For each unique number of clusters, store the max variance explained and its rmsd */
	for ( i=0 ; i < 2000 ; i++ )
		{
			variances[i][0] = -1.0;
			variances[i][1] = -1.0;
		}
	for ( i=10 ; i <= 200 ; i++ )
		if ( variances[ nof_cl[ i ] ][0] < var_expl[ i ] )
			{
				variances[ nof_cl[ i ] ][0] = var_expl[ i ];
				variances[ nof_cl[ i ] ][1] = i / 10.0l;
			}



	/* Write out data ... */
	
	out = fopen("carma.variance_explained.dat", "w");
	if ( out == NULL )
		{	
			printf("\033[31m\033[1mCan not open a 'carma.variance_explained.dat' file for writing. Abort.\033[0m\n");
			myexit(1);
					}
	for ( i=1 ; i <= max_clust ; i++ )
		if ( variances[ i ][0] > -0.50 )
			fprintf( out, "%3d  %6.4f  %6.2f\n", i, variances[ i ][0], variances[ i ][1] );
	
	fclose( out );




	/* If a number of clusters has not been observed, use the values from the previous ones */
	for ( i=1 ; i <= max_clust ; i++ )
		if ( variances[ i ][0] > -0.50 )
			break;
	
	for ( k=1 ; k < i ; k++ )
		{
			variances[ k ][0] = variances[ i ][0];
			variances[ k ][1] = variances[ i ][1];
		}
	
	for ( i=1 ; i < max_clust ; i++ )
		{
			if ( variances[ i+1 ][0] < 0.0 )
				{
					variances[ i+1 ][0] = variances[ i ][0];
					variances[ i+1 ][1] = variances[ i ][1];
				}	
		}



	/* Calculate running differences weighted by variance explained */
	for ( i=1 ; i <= max_clust-1 ; i++ )
		{
			differences[i+1][0] = variances[ i+1 ][0] * (variances[ i+1 ][0] - variances[ i ][0]) ;
			differences[i+1][1] = variances[ i+1 ][1];
			
			/* printf("%d %+6.4f %+6.4f\n", i+1, differences[i+1][0], differences[i+1][1] ); */
		}



	if ( max_clust == 1 || (variances[ 1 ][0] > 0.90 && max_clust < 3))  /* We are done, one cluster */
		{
			CLU_RMS = variances[ 1 ][1];
		}
	else
	{
		float	max_diff = -1.0;
		int	max_pos = -1;
		
		for ( i=2 ; i <= max_clust ; i++ )			/* Find largest running difference */
			{
				if ( differences[i][0] > max_diff )
					{
						max_diff = differences[i][0];
						max_pos = i;
					}
			}
	
		CLU_RMS = variances[ max_pos ][1];
										/* If variance explained is low, try with */
										/* the next (lower) peak                  */
		if ( variances[ max_pos ][0] < 0.75 && max_pos < max_clust-1 )		
		{
			float   max_diff2 = -1.0;
			int     max_pos2 = -1;
			
			for ( i=max_pos+1 ; i <= max_clust ; i++ )
				{
					if ( differences[i][0] > max_diff2 )
					{
						max_diff2 = differences[i][0];
						max_pos2 = i;
					}
				}
			
			if ( variances[ max_pos2 ][0] > 0.80 )
				{
					CLU_RMS = variances[ max_pos2 ][1];
					if ( VERBOSE )
					printf("Using the second-best solution to obtain a variance explained higher than 0.80.\n");
					
				}
			else
				CLU_RMS = variances[ max_pos ][1];
			
		}
	
	}


	
	if ( VERBOSE )
		printf("Cutoff for cluster analysis set to %4.2f\n", CLU_RMS );
	

	cutoff = aver + CLU_RMS * rmsd;

	for ( i=1 ; i <= bins ; i++ )	
	for ( k=1 ; k <= bins ; k++ )	
	for ( m=1 ; m <= bins ; m++ )	
		CLUSTER[i][k][m] = original[i][k][m];

	maxx = 0;
	maxy = 0;
	maxz = 0;
	current_peak = 1;

	MAP_VARIANCE = 0.0;

	while ( 1 )
	{

	current_max = -1.0;
	for ( i=1 ; i <= bins ; i++ )	
	for ( k=1 ; k <= bins ; k++ )	
	for ( m=1 ; m <= bins ; m++ )	
		if ( (val=CLUSTER[i][k][m]) > current_max && val < 999999.0 ) 
			{
				current_max = val;
				maxx = i;
				maxy = k;
				maxz = m;
			}

	if ( current_max < cutoff )
		break;

	erase_peak( cutoff, maxx, maxy, maxz, current_max, 1000000.0+current_peak, bins);
	current_peak++;
	}

	current_peak--;

	if (VERBOSE)
		printf("Number of clusters %d, explained map variance %4.2f\n", current_peak, MAP_VARIANCE / ( GRID_POINTS * MAP_RMSD * MAP_RMSD) );

	if ( MAP_VARIANCE / ( GRID_POINTS * MAP_RMSD * MAP_RMSD) < 0.65 )
		printf("\033[33mVariance explained is low. Consider using a different cluster analysis method.\033[0m\n");
		

	}




	for ( i=0 ; i < 10000 ; i++ )
		populations[i] = 0;

	for ( i = 1 ; i <= frames ; i++ )
	{
		val1 = DG[i][1];
		val2 = DG[i][2];
		val3 = DG[i][3];
		
		pos1 = (int)( bins * (val1 + limit) / (2.0*limit) + 0.50 )+1;
		pos2 = (int)( bins * (val2 + limit) / (2.0*limit) + 0.50 )+1;
		pos3 = (int)( bins * (val3 + limit) / (2.0*limit) + 0.50 )+1;
	
		if ( CLUSTER[pos1][pos2][pos3] > 999999 )
			{
			fprintf(clusters, "%8d %3d %12.7f %12.7f %12.7f\n", 
					i, (int)(CLUSTER[pos1][pos2][pos3]-1000000+0.2), val1, val2, val3 );
			populations[ (int)(CLUSTER[pos1][pos2][pos3]-1000000+0.2) ]++;
			}
		

	}

	if (VERBOSE)
	{
	printf("Cluster frequencies:\n");
	for ( i=1 ; i <= current_peak ; i++ )
		{
			printf("\t Cluster %3d : %8d out of %8d frames (%+7.3f kcal/mol)\n", i, populations[ i ], frames, -0.239005736* 8.314472 * DGTEMP * log( populations[ i ] / (double)(frames - populations[ i ]) )/1000.0 );
		}
	}	
	


}



void	erase_peak( cutoff, x, y, z, top_of_peak, pval, bins )
float	cutoff;
int	x, y, z;
float	top_of_peak;
float	pval;
int	bins;
{
	float	val;


	if ( x < 2 || x > bins-1 ||  y < 2 || y > bins-1 || z < 2 || z > bins-1 )
	{
		printf("\033[31m\033[1m\n\nCluster analysis made a boo boo! Goodbye.\033[0m\n");
		printf("\033[33m[this is possibly means that the number of\nframes used for the analysis is too small].\033[0m\n");
		exit(1);
	}


	MAP_VARIANCE += ( CLUSTER[x][y][z] - MAP_AVER ) * ( CLUSTER[x][y][z] - MAP_AVER );
	
	CLUSTER[x][y][z] = pval;

	if ( (val=CLUSTER[x][y][z+1]) > cutoff && val < 999999.0 )
		erase_peak( cutoff, x, y, z+1, val, pval, bins );
	if ( (val=CLUSTER[x][y][z-1]) > cutoff && val < 999999.0 )
		erase_peak( cutoff, x, y, z-1, val, pval, bins );

	if ( (val=CLUSTER[x][y+1][z+1]) > cutoff && val < 999999.0 )
		erase_peak( cutoff, x, y+1, z+1, val, pval, bins );
	if ( (val=CLUSTER[x][y+1][z]) > cutoff && val < 999999.0 )
		erase_peak( cutoff, x, y+1, z, val, pval, bins );
	if ( (val=CLUSTER[x][y+1][z-1]) > cutoff && val < 999999.0 )
		erase_peak( cutoff, x, y+1, z-1, val, pval, bins );

	if ( (val=CLUSTER[x][y-1][z+1]) > cutoff && val < 999999.0 )
		erase_peak( cutoff, x, y-1, z+1, val, pval, bins );
	if ( (val=CLUSTER[x][y-1][z]) > cutoff && val < 999999.0 )
		erase_peak( cutoff, x, y-1, z, val, pval, bins );
	if ( (val=CLUSTER[x][y-1][z-1]) > cutoff && val < 999999.0 )
		erase_peak( cutoff, x, y-1, z-1, val, pval, bins );


	if ( (val=CLUSTER[x+1][y][z+1]) > cutoff && val < 999999.0 )
		erase_peak( cutoff, x+1, y, z+1, val, pval, bins );
	if ( (val=CLUSTER[x+1][y][z]) > cutoff && val < 999999.0 )
		erase_peak( cutoff, x+1, y, z, val, pval, bins );
	if ( (val=CLUSTER[x+1][y][z-1]) > cutoff && val < 999999.0 )
		erase_peak( cutoff, x+1, y, z-1, val, pval, bins );

	if ( (val=CLUSTER[x+1][y+1][z+1]) > cutoff && val < 999999.0 )
		erase_peak( cutoff, x+1, y+1, z+1, val, pval, bins );
	if ( (val=CLUSTER[x+1][y+1][z]) > cutoff && val < 999999.0 )
		erase_peak( cutoff, x+1, y+1, z, val, pval, bins );
	if ( (val=CLUSTER[x+1][y+1][z-1]) > cutoff && val < 999999.0 )
		erase_peak( cutoff, x+1, y+1, z-1, val, pval, bins );

	if ( (val=CLUSTER[x+1][y-1][z+1]) > cutoff && val < 999999.0 )
		erase_peak( cutoff, x+1, y-1, z+1, val, pval, bins );
	if ( (val=CLUSTER[x+1][y-1][z]) > cutoff && val < 999999.0 )
		erase_peak( cutoff, x+1, y-1, z, val, pval, bins );
	if ( (val=CLUSTER[x+1][y-1][z-1]) > cutoff && val < 999999.0 )
		erase_peak( cutoff, x+1, y-1, z-1, val, pval, bins );


	if ( (val=CLUSTER[x-1][y][z+1]) > cutoff && val < 999999.0 )
		erase_peak( cutoff, x-1, y, z+1, val, pval, bins );
	if ( (val=CLUSTER[x-1][y][z]) > cutoff && val < 999999.0 )
		erase_peak( cutoff, x-1, y, z, val, pval, bins );
	if ( (val=CLUSTER[x-1][y][z-1]) > cutoff && val < 999999.0 )
		erase_peak( cutoff, x-1, y, z-1, val, pval, bins );

	if ( (val=CLUSTER[x-1][y+1][z+1]) > cutoff && val < 999999.0 )
		erase_peak( cutoff, x-1, y+1, z+1, val, pval, bins );
	if ( (val=CLUSTER[x-1][y+1][z]) > cutoff && val < 999999.0 )
		erase_peak( cutoff, x-1, y+1, z, val, pval, bins );
	if ( (val=CLUSTER[x-1][y+1][z-1]) > cutoff && val < 999999.0 )
		erase_peak( cutoff, x-1, y+1, z-1, val, pval, bins );

	if ( (val=CLUSTER[x-1][y-1][z+1]) > cutoff && val < 999999.0 )
		erase_peak( cutoff, x-1, y-1, z+1, val, pval, bins );
	if ( (val=CLUSTER[x-1][y-1][z]) > cutoff && val < 999999.0 )
		erase_peak( cutoff, x-1, y-1, z, val, pval, bins );
	if ( (val=CLUSTER[x-1][y-1][z-1]) > cutoff && val < 999999.0 )
		erase_peak( cutoff, x-1, y-1, z-1, val, pval, bins );


}









/*********************************************************************************************************************************/
/** Write out the map in one of the three available formats : ASCII, NA4, CCP4						 	**/
/*********************************************************************************************************************************/

void	write_map( title, data, slow, med, fast, iuvw, mode, details, cell )
char	*title;
float	***data;
int	iuvw[3];
int	slow;
int	med;
int	fast;
int	mode;
char 	*details;
float	cell[6];
{
	FILE	*file;
	int	u, v, w;
	float	val;
	int	x, y, z;
	float	min, max, mean, rms;
	float	scale;
	int	m;
	int	INDXR4_1, INDXR4_2;
	int	I, N;
	float	A, P;
	char 	string[4];




	for ( m = 0 ; m <= strlen( &details[0] ) ; m++ )
		if ( details[m] == '\n' )
			details[m] = 0;



	/*********************************************************************************************************************************/
	/**  Calculate map statistics, scale to a maximum of 999									**/
	/*********************************************************************************************************************************/
			

        max  = data[1][1][1];
	mean = 0.0;
        for ( w=1 ; w <= slow ; w++ )
        for ( v=1 ; v <= med  ; v++ )
        for ( u=1 ; u <= fast ; u++ )
		{
		val = data[w][v][u];
                if ( val > max )
			max = val;
		mean += val;
				}
	
	if ( VERBOSE )
		printf("Writing map in NA4 format ...\n" );
	

	scale = 999.0 / max;
	
	if ( VERBOSE )
		printf("Scale factor applied for NA4 map: %15.8f.\n", scale );

        for ( w=1 ; w <= slow ; w++ )
        for ( v=1 ; v <= med  ; v++ )
        for ( u=1 ; u <= fast ; u++ )
		data[w][v][u] *= scale;		
		


        min  = data[1][1][1];
        max  = min;
        mean = 0.0;
        rms  = 0.0;
        for ( w=1 ; w <= slow ; w++ )
        for ( v=1 ; v <= med  ; v++ )
        for ( u=1 ; u <= fast ; u++ )
                {
                        val = data[w][v][u];
                        if ( val > max )
                                max = val;
                        if ( val < min )
                                min = val;
                        mean += val;
                                                }
        mean /= (float)(slow*med*fast);

        for ( w=1 ; w <= slow ; w++ )
        for ( v=1 ; v <= med  ; v++ )
        for ( u=1 ; u <= fast ; u++ )
                {
                        val = data[w][v][u];
			rms += ( val - mean ) * ( val - mean );
				}
        rms = (float)(sqrt( rms / (double)(slow*med*fast - 1.0)));




			
	/*********************************************************************************************************************************/
	/**  NA4 format.														**/
	/*********************************************************************************************************************************/


	/* Re-writing FORTRAN ... */
	

	A = max2( fabs(min), fabs(max));
	P = 24.0 - log( A ) / log( 2.0 );
	if ( P < 0.0 )
		I = P - 1;
	else
		I = P;
	
	if ( I == 0 )
		N = A;
	else
		if ( I == 1 )
			N = 2 * A;
		else
			N = A * ( 2 << (I-1));
	
	if ( N < (2 << 22)) 
		I = I + 1;
	else
	if ( N > (2 << 23))
		I = I - 1;
		

	N = 0;
	if ( min < 0.0 )
		N = N - 1;
	else
		if ( min > 0.0 )
			N = N + 1;
	if ( max < 0.0 )
		N = N - 1;
	else
		if ( max > 0.0 )
			N = N + 1;
		
	INDXR4_1 = N;
	if ( N == 0 )
		INDXR4_2 = I - 1;
	else
		INDXR4_2 = I;
	
	

	file = fopen( title, "w" );
	if ( file == NULL )
		{
			fclose ( file );
			printf("Failed to create the output map file.\n\n\n");
			exit( 0 );
						}

	x = 0;
	y = 0;
	z = 0;
	if ( iuvw[0] == 1 )
		x = fast;
	if ( iuvw[0] == 2 )
		y = fast;
	if ( iuvw[0] == 3 )
		z = fast;
	if ( iuvw[1] == 1 )
		x = med;
	if ( iuvw[1] == 2 )
		y = med;
	if ( iuvw[1] == 3 )
		z = med;
	if ( iuvw[2] == 1 )
		x = slow;
	if ( iuvw[2] == 2 )
		y = slow;
	if ( iuvw[2] == 3 )
		z = slow;


	fprintf(file, "MAPTONA4 HEADER\n");
	fprintf(file, "TITLE   \n");
	fprintf(file, "%s\n", &details[0]);
	fprintf(file, "AXIS           %c       %c       %c\n", 'X'+iuvw[0]-1, 'X'+iuvw[1]-1, 'X'+iuvw[2]-1 );
	fprintf(file, "GRID       % 5d   % 5d   % 5d\n", x, y, z);
	fprintf(file, "XYZLIM         0   % 5d       0   % 5d       0   % 5d\n", x-1, y-1, z-1);
	fprintf(file, "SPACEGROUP          % 4d\n", 1);
	fprintf(file, "MODE           %d\n", mode);
	fprintf(file, "CELL    % 10.3f% 10.3f% 10.3f% 10.3f% 10.3f% 10.3f\n",cell[0],cell[1],cell[2],cell[3],cell[4],cell[5]);
	fprintf(file, "RHOLIM% 16.6f% 16.6f% 16.6f% 16.6f\n", min, max, mean, rms);
	fprintf(file, "INDXR4  % 4d% 4d\n", INDXR4_1, INDXR4_2);
	fprintf(file, "END HEADER\n");


        for ( w=1 ; w <= slow ; w++ )
	{
	fprintf( file , "\nSECTION% 8d\n\n", w-1 );
	
        for ( v=1 ; v <= med  ; v++ )
        for ( u=1 ; u <= fast ; u += 20 )
                {
			for ( m=u ; m < ( fast < (u+20) ? fast+1 : u+20 ) ; m++ )
				{
				tona4( &string[0], data[w][v][m], INDXR4_1, INDXR4_2);
				fprintf(file,"%c%c%c%c", string[0], string[1], string[2], string[3]);
				}
			fprintf(file, "\n");
					}
						}
						
			
			
			



	fclose(file);

}



	
/* Re-writing FORTRAN : routine from maptona4 (Phil Evans), originally due to Ian Tickle, Birkbeck. */

void tona4( string, val, INDXR4_1, INDXR4_2)
char 	*string;
float	val;
int	INDXR4_1, INDXR4_2;
{

	int 	I, J, M, N;
	const char	CHRTAB[65] = "0123456789-+ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	
	
	if ( val == 0.0 )
		strncpy( string, "0000", 4);
	
	else
		{
			if ( INDXR4_2 == 0 )
				N = nearint( fabs(val) );
			else
			if ( INDXR4_2 == 1 )
				N = nearint( 2 * fabs(val) );
			else
				N = nearint( fabs(val) * ( 2 << (INDXR4_2-1)) );
			
			if ( INDXR4_1 == 0 )
				M = 2 << 22;
			else
				M = 2 << 23;
			
			if ( N == M )
				N = M - 1;
			else
			if ( N > M )
				{
				strncpy( string, "****", 4);
				return;
				}
			
			if ( INDXR4_1 == 0 && val < 0.0 )
				N = ( 2 << 23 ) - N;
			
			for ( I=4 ; I >= 1 ; I-- )
				{
					M = N / 64;
					J = N - 64*M;
					string[I-1] = CHRTAB[J];
					N = M;
						}
							}
	return;
}

