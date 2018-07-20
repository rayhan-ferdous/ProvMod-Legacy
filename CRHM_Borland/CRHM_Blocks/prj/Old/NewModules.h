// 07/13/12
//---------------------------------------------------------------------------

#ifndef OurModulesH
#define OurModulesH
//---------------------------------------------------------------------------

#include "ClassModule.h"

using namespace std;

extern "C" void __declspec(dllexport) MoveModulesToGlobal(String DLLName = "CRHM");

class Classshared : public ClassModule {
public:

Classshared(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared parameters

// declared variables

void decl(void);
void init(void);

Classshared* klone(string name) const;
};

class Classbasin : public ClassModule {
public:

Classbasin(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared parameters
const long *RUN_ID;
const long *RUN_START;
const long *RUN_END;

const float *Meyer_B;
const float *basin_area;   // [BASIN]
const float *hru_area;
const float *hru_lat;
const float *hru_elev;
const float *hru_GSL;
const float *hru_ASL;

TStringList *basin_name;
TStringList *INIT_STATE;
TStringList *hru_names;
TStringList *RapidAdvance_to;
TStringList *Loop_to;
TStringList *StateVars_to_Update;
TStringList *TraceVars;

// declared variables
long *run_ID;

void decl(void);
void init(void);

Classbasin* klone(string name) const;
};

class Classglobal : public ClassModule {
public:

Classglobal(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
float *QdroD;
float *QdroDext;
float *QdfoD;
float *Qdro;
float *Qdfo;
float *Qdflat;
float *QdflatD;
float *QdflatE;
float *SolAng;
float *SunMax;
float *cosxs;
float *cosxsflat;
float *pQdro;
float **pQdro_FREQ;
float *pQdfo;
float **pQdfo_FREQ;
float *pQdflat;
float **pQdflat_FREQ;
float *pQdflatE;
float **pQdflatE_FREQ;
float *pSol;
float **pSol_FREQ;
float *pCosxs;
float **pCosxs_FREQ;
float *pCosxs0;
float **pCosxs0_FREQ;

// declared parameters
const float *hru_lat;
const float *hru_elev;
const float *hru_GSL;
const float *hru_ASL;
const float *Time_Offset;

//const long  *Extra;

// variable inputs

void air_mass (const float czen, float &oam);

void decl(void);
void init(void);
void run(void);

Classglobal* klone(string name) const;
};

class Classobs : public ClassModule {
public:

Classobs(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

long Exist;

// declared observation variables
const float *p;      // interval data
const float *ppt;    // daily data
const float *t;
float **tday_intvls;
const float *rh;
float **rhday_intvls;
const float *ea;
float **eaday_intvls;
const float *u;
const float *t_max;
const float *t_min;

// declared observation functions
float *tmean;
float *tmin;
float *tmax;
float *umean;
float *pptD;
float *NotUsed;

// declared variables
float *hru_t;
float *hru_rh;
float *hru_ea;
float *hru_u;
float *hru_p;
float *Pa;
float *hru_rain;
float *cumhru_rain;
float *hru_snow;
float *cumhru_snow;
float *hru_tmax;
float *hru_tmin;
float *hru_tmean;
float *hru_eamean;
float *hru_umean;
float *hru_rhmean;

float *t_obs;
float **t_obs_lay;

long  *hru_newsnow;

// declared parameters
const float *basin_area;   // [BASIN]
const float *hru_area;
const float *tmax_allrain;
const float *tmax_allsnow;
const float *lapse_rate;
const float *precip_elev_adj;
const float *obs_elev;
const float *hru_elev;
const float *ClimChng_t;
const float *ClimChng_precip;
const long  *catchadjust;
const long  *ppt_daily_distrib;
const long  *snow_rain_determination;
const long  *HRU_OBS;
const long  **HRU_OBS_Tables;
const long  *ElevChng_flag;

// variable inputs

void decl(void);
void init(void);
void run(void);
void pre_run(void);
void finish(bool good);

Classobs* klone(string name) const;
};

class Classintcp : public ClassModule {
public:

Classintcp(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
float *net_rain;
float *cumnet_rain;
float *net_snow;
float *net_p;
float *intcp_evap;

// declared parameters
const float *basin_area;
const float *hru_area;

// variable inputs
const float *hru_rain;
const float *hru_snow;
const float *hru_p;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classintcp* klone(string name) const;
};

class Classpbsm : public ClassModule {
public:

Classpbsm(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 1001), // setting PeerRank
                                  hru_basin(NULL) {};
float hru_u_;

// declared variables

float *SWE;
float *Subl;
float *Drift;
float *cumSubl;
float *cumDrift;
float *cumDriftIn;
float *cumSno;
float *Prob;
float *snowdepth;
float *BasinSnowLoss;
float *cumBasinSnowLoss;
float *cumBasinSnowGain;
float *SnowAge;
float *SWE_Init;
long  *DrySnow;

// declared parameters
const float *fetch;
const float *Ht;
const float *distrib;
const float *basin_area;
const float *hru_area;
const float *A_S;
const float *N_S;
const long *inhibit_evap;
const long *inhibit_bs;
const long *inhibit_subl;

// variable inputs
const float *hru_t;
const float *hru_rh;
const float *hru_u;
const float *hru_Uadjust;
const float *net_snow;
const long  *hru_newsnow;

// local allocated arrays
float *hru_basin;


void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classpbsm* klone(string name) const;
};

class ClassNO_pbsm : public ClassModule {
public:

ClassNO_pbsm(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 1001), // setting PeerRank =1
                                  hru_basin(NULL) {};
// declared variables
float *SWE;
float *cumSno;
float *snowdepth;

// declared parameters
const float *basin_area;
const float *hru_area;
const long *inhibit_evap;

// variable inputs
const float *net_snow;
const long  *hru_newsnow;

// local allocated arrays
float *hru_basin;


void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassNO_pbsm* klone(string name) const;
};

class Classalbedo : public ClassModule {
public:

Classalbedo(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
float *Albedo;
float *net_snowD;  // daily value sum(newsnow)
long *meltflag;
long *winter;
long  *newsnowcnt;

// declared parameters
const float *Albedo_bare;
const float *Albedo_snow;
const float *hru_lat;

// variable inputs
const float *hru_tmax;
const float *hru_tmin;
const float *QdroD;
const float *SWE;
const float *net_snow;
const long  *hru_newsnow;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classalbedo* klone(string name) const;
};

class Classnetall : public ClassModule {
public:

Classnetall(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared observation variables
const float *t;
const float *ea;
const float **tday_intvls;
const float **eaday_intvls;
const float *NotUsed;

// declared variables
float *net;
float *Rn; // net converted to mm
float *netD;
float *RnD; // netD converted to mm
float *RnD_POS;
float *cum_net;

// declared parameters

// variable inputs
const float *hru_t;
const float *hru_ea;
const float *Albedo;
const float *hru_SunAct;
const float *SunMax;
const float *Qdro;
const float *Qdfo;
const float *pQdro;
const float *pQdfo;
const float **pQdro_FREQ;
const float **pQdfo_FREQ;

void decl(void);
void init(void);
void run(void);

Classnetall* klone(string name) const;
};

class Classebsm : public ClassModule {
public:

Classebsm(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl){};

// declared observation variables
const float *Qnsn;
const float *QnD;

// declared variables
float *snowmeltD;
float *cumsnowmelt;
float *LW_ebsm;
float *u_ebsm;
float *Qmelt;
float *Qn_ebsm;
float *Qh_ebsm;
float *Qe_ebsm;
float *Qp_ebsm;
float *Qnsn_Acc;

float *LWmax;
float *net_rainD;

// declared parameters
const float *basin_area;   // [BASIN]
const float *hru_area;
const float *tfactor;
const float *nfactor;
const float *Use_QnD;

// variable inputs
float *SWE;
const float *tmean;
const float *tmax;
const float *tmin;
const float *umean;
const float *rhmean;
const float *net_rain;
const float *Albedo;
const float *sunact;
const float *QdroD;
const float *QdfoD;
const float *sunmax;
const float *Qnsn_Var;

const long  *meltflag;
const long  *delay_melt;

// local allocated arrays

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classebsm* klone(string name) const;
};

class ClassTs : public ClassModule {

    public:

    ClassTs(string Name, String Version = "Radiation", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared observations
    float *Ts;

// declared observation variables

    const float *hru_u;

    const float *hru_t;

    const float *hru_rh;

    const float *Qli;

// declared variables

   float *hru_Ts;

   float *Pa;

   float *q;

   float *ra;

// declared parameters

   const float *Ht;

   const float *Zref;

   const float *Zwind;

   const float *hru_elev;

   const float *Z0snow; // snow roughness length (m)

// variable inputs


    void decl(void);
    void init(void);
    void run(void);

ClassTs* klone(string name) const;
};

class ClassNeedle : public ClassModule {

    public:

    ClassNeedle(string Name, String Version = "Undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

    float Qli_;

    float Qsi_;

// declared observations

    float *Ts;

    float *Qnsn;

    float *Qsisn;

    float *Qlisn;

    float *Qlosn;

// declared observation variables

    const float *Qsi;

    const float *Qli;

    const float *QsiA_Var;

    const float *QsiS_Var;

    const float *QliVt_Var;

// declared variables

   float *Pa;

   float *k;

   float *Tauc;

   float *ra;

   float *Qnsn_Var;

// declared parameters

   const float *LAI;

   const float *Ht;

   const float *Zwind;

   const float *Zref;

   const float *hru_elev;

   const float *Z0snow; // snow roughness length (m)


// variable inputs

    const float *beta;

    const float *SWE;

    const float *Albedo;

    const float *hru_t;

    const float *hru_u;

    const float *hru_ea;

    const float *hru_rh;


    void decl(void);

    void init(void);

    void run(void);

ClassNeedle* klone(string name) const;
};

class ClassSimpleRichard : public ClassModule {

    public:

    ClassSimpleRichard(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared observation variables

    const float *Qsi;  // Downward shortwave radiation (W/m2)
    const float *Qli;  // Downward longwave radiation (W/m2)
    const float *snow; // Snowfall (kg/m2/s)
    const float *t;    // Air temperature (�K)
    const float *u;    // Wind speed (m/s)
    const float *rh;   // Relative humidity (%)

// declared variables

    float *SWE;       // (kg/m2)
    float *alb;       // Snow albedo
    float *snowmelt;  // (kg/m2)
    float *meltclark; // (kg/m2)
    float *sursubl;   // (kg/m2)
    float *T0;   // Surface temperature (�K)

    float *LE;   // Latent heat flux (W/m^2)
    float *H;    // Sensible heat flux (W/m^2)
    float *Hsm;  // Snowmelt heat flux (W/m^2)
    float *LWn;  // Net longwave radiation (W/m^2)
    float *SWn;  // Net shortwave radiation (W/m^2)

// declared parameters

    const float *a1;   // Albedo decay time constant for cold snow (s)
    const float *a2;   // Albedo decay time constant for melting snow (s)
    const float *amin; // Minimum albedo for aged snow
    const float *amax; // Maximum albedo for fresh snow
    const float *smin; // Minimum snowfall to refresh snow albedo (mm)
    const float *Ht;   // Roughness length
    const float *Zref;   // Reference height
    const float *Pa;   // Average surface pressure (KPa)
    const float *Kstorage; // [nhru]
    const float *Lag;      // [nhru]
    const float *Z0snow;   // snow roughness length (m)

// variable inputs

    void decl(void);

    void init(void);

    void run(void);

    void finish(bool good);

    ClassSimpleRichard* klone(string name) const;

    void EXCH(long hh, float Q1, float U1, float &CH);

    void ALBEDO(long hh);

    void SURF(long hh, float Q1, float U1);

// local class

    ClassClark *Delays;

    float dt;
};

class Classevap : public ClassModule {
public:

Classevap(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
float *hru_actet;
float *hru_cum_actet;
float *evap;
float *evapD;
float *cum_evap;
float *evapGrangerD;
float *G;
float *D;

// local allocated arrays
float *Pa;

// declared parameters
const float *basin_area;   // [BASIN]
const float *hru_area;
const float *Ht;
const float *hru_elev;
const float *F_Qg;
const float *rs;
const float *Zwind;

const long *evap_type;
const long *inhibit_evap;

// variable inputs
const float *Rn;
const float *RnD;
const float *RnD_POS;
const float *hru_t;
const float *hru_u;
const float *hru_ea;
const float *hru_tmean;
const float *hru_umean;
const float *hru_eamean;

// declared observations variable

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classevap* klone(string name) const;

double gamma(float Pa, float t);         // Psychrometric constant
float lambda(float t);                   // Latent heat of vaporization
double delta(float t);                   // Slope of sat vap p vs t, kPa/�C
float RHOa(float t, float ea, float Pa); // atmospheric density (kg/m^3)
double fdaily(float u, float Ht);        // Drying power f(u) - interval
};

class ClassevapD : public ClassModule {
public:

ClassevapD(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
float *hru_actet;
float *hru_cum_actet;
float *evapD;
float *cum_evap;
float *G;
float *D;

// local allocated arrays
float *Pa;


// declared parameters
const float *basin_area;   // [BASIN]
const float *hru_area;
const float *Ht;
const float *hru_elev;
const float *F_Qg;

const long *evap_type;
const long *inhibit_evap;

// variable inputs
const float *RnD;
const float *hru_tmean;
const float *hru_umean;
const float *hru_eamean;

// variable puts

// declared observations variable

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassevapD* klone(string name) const;

double gamma(float Pa, float t);         // Psychrometric constant
float lambda(float t);                   // Latent heat of vaporization
double delta(float t);                   // Slope of sat vap p vs t, kPa/�C
float RHOa(float t, float ea, float Pa); // atmospheric density (kg/m^3)
double fdaily(float u, float Ht);        // Drying power f(u) - interval
};

class Classsbsm : public ClassModule {
public:

Classsbsm(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 1001), // setting PeerRank =1
                                  hru_basin(NULL) {};
float dt;

// declared variables
float *SWE;
float *wet_snow;
float *Subl;
float *Drift;
float *cumSubl;
float *cumDrift;
float *cumDriftIn;
float *cumSno;
float *Prob;
float *snow_age;
float *BasinSnowLoss;
float *cumBasinSnowLoss;
float *cumBasinSnowGain;
float *snowdepth;

// declared parameters
const float *basin_area;
const float *hru_area;
const float *Ht;
const float *zr;
const float *distrib;
const float *fetch;
const long *inhibit_evap;
const long *inhibit_subl;

// variable inputs
const float *hru_t;
const float *hru_rh;
const float *hru_u;
const float *net_snow;
const long  *hru_newsnow;

// local allocated arrays
float *hru_basin;


void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classsbsm* klone(string name) const;

float transport(void);
float sublimation(void);
float scale(void);
void  prob(void);
};

class Classcrack : public ClassModule {
public:

Classcrack(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl),
                                   Xinfil(NULL),
                                   timer(NULL) {};
// declared variables
float *snowinfil;
float *cumsnowinfil;
float *infil;
float *cuminfil;
float *meltrunoff;
float *cummeltrunoff;
float *runoff;
float *cumrunoff;
float *RainOnSnow;
float *RainOnSnowA;
long  *crackstat;
long  *crackon;

// declared parameters
const float *basin_area; // [BASIN]
const float *hru_area;
const float *fallstat;
const float *Major;      // threshold for major melt event(default is 5 mm/day)
const long  *PriorInfiltration;

// variable inputs
const float *hru_tmax;
const float *snowmelt;
const float *SWE;
const float *net_rain;

// local allocated arrays
float **Xinfil; // [3] [nhru]
long *timer;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classcrack* klone(string name) const;
};

class ClassKevin : public ClassModule {
public:

ClassKevin(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl),
                                   SWEpeak(NULL),
                                   SWElast(NULL) {};
// declared observation variables

// declared variables
float *albedo;
float *sca;
float *snowmelt;
float *snowmeltD;
float *cumsnowmelt;
float *netLong;
float *netShort;
long  *winter;
long  *SnowStat;

// declared parameters
const float *Asnow1;
const float *Asnow2;
const float *Asoil;
const float *cv;
const float *tfactor;
const float *nfactor;
const float *meltthresh;
const float *basin_area;   // [BASIN]
const float *hru_area;
const float *hru_lat;

// variable inputs
float *SWE;
const float *hru_t;
const float *hru_tmean;
const float *hru_eamean;
const float *hru_Qn;
const float *hru_SunAct;
const float *Qdro;
const float *Qdfo;
const float *SunMax;

// local allocated arrays
float   *SWEpeak;
float   *SWElast;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassKevin* klone(string name) const;
};

class ClassGreencrack : public ClassModule {
public:

ClassGreencrack(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl),
                                   Xinfil(NULL),
                                   timer(NULL) {};
// declared variables
float *infil;
float *cuminfil;
float *meltrunoff;
float *cummeltrunoff;
float *runoff;
float *cumrunoff;
float *snowinfil;
float *cumsnowinfil;
long  *crackstat;
long  *crackon;
float *RainOnSnow;
float *RainOnSnowA;

// local variables
float *k;
float *F0;
float *f0;
float *F1;
float *f1;
float *dthbot;
float *psidthbot;
long  *timer;

// declared parameters
const float *basin_area; // [BASIN]
const float *hru_area;
const float *fallstat;
const float *Major;      // threshold for major melt event(default is 5 mm/day)
const float *soil_moist_max;
const float *soil_moist_init;
const long  *soil_type;
const long  *PriorInfiltration;

// variable inputs
const float *hru_tmax;
const float *snowmelt;
const float *SWE;
const float *net_rain;
float *soil_moist; // changed tp PUT

// class allocated
float garain;      // precipitation/int
float intensity;   // precipitation/int converted to mm/h
float pond;        // mm

// class allocated arrays
float **Xinfil; // [3] [nhru]

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassGreencrack* klone(string name) const;

void infiltrate(void);
void ponding(void);
void startponding(void);
void howmuch(float F0, float dt);

float calcf1(float F, float psidth);
};

class Classfrostdepth : public ClassModule {
public:

Classfrostdepth(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl),
                                        k_lay(NULL),
                                        L_lay(NULL),
                                        c_lay(NULL),
                                        Lacc(NULL),
                                        Cacc(NULL),
                                        Kacc(NULL) {};
// declared variables
float *frostdepth;
float *snowdepth;
float *Findex;   // freezing index (days * frost �C)
long *Tfreeze;   // duration of freezing period in days

// declared parameters
const float *Ta;        // mean annual air temperature
const float *d;         // depth of layer  m
const float **d_lay;    // depth of layer  m
const float *por;       // porosity m3/m3
const float **por_lay;  // porosity m3/m3
const float *theta;       // theta m3/m3  theta/porosity
const float **theta_lay;  // theta m3/m3
const long  *soil_type;
const long  **soil_type_lay;
const float *hru_lat;

// variable inputs
const float *hru_tmean;  // daily average temperature (�C)
const float *SWE;

// local allocated arrays
float **k_lay;    // J/(m.K.s)
float **L_lay;    // MJ/m3
float **c_lay;    // MJ/(m3 K)
float *Lacc; // effective value
float *Cacc; // effective value
float *Kacc; // effective value

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classfrostdepth* klone(string name) const;
};

class Classfrozen : public ClassModule {
public:

Classfrozen(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl),
                                    infiltype(NULL) {};
bool SetOpportunityTime;
float SWE_sum;

// declared observation variables
const float *t0_inhibit;   // (mm/day)

// declared variables
float *infil;         // unfrozen infiltration
float *cuminfil;      // cumulative unfrozen infiltration
float *snowinfil;     // frozen infiltration
float *cumsnowinfil;  // cumulative frozen infiltration
float *cummeltrunoff; // cumulative frozen melt runoff
float *runoff;        // cumulative runoff
float *cumrunoff;     // cumulative melt runoff
float *t0_Acc;        // infiltration opportunity time accumulation
float *t0_Var;        // infiltration opportunity value used in calculation
float *INF;
float *snowmeltD_last; //
long  *Julian_window; // currently in Julian window.
long  *Julian_end;    // Julian window end date.

// variable put
const float *soil_moist;    //
float *meltrunoff;      // [nhru]

// local variables
long *infiltype;
float *SWE_pk;           //

// declared parameters
const float *basin_area;  // [BASIN]
const float *hru_area;
const float *S0;          // surface saturation (mm3/mm3)
const float *Si;          // initial average soil saturation (mm3/mm3)
const float *C;           // coefficient
const float *hru_tsoil;   // soil temperature(�K) of 0-40cm soil layer at start of infiltration
const float *t_ice_lens;   // overnight minimum to cause ice lens after major melt
const float *t0;          // infiltration opportunity time. Set at end of calibration run.
const float *soil_moist_max; // common to smbal to control maximum inflitration.
const long  *t0_Julian;    // Julian date when t0 is primed. '0' value - never reset.

// variable inputs
const float *snowmeltD;   // (mm/day)
const float *SWE;         // (mm)
const float *frostdepth;
const float *net_rain;
const float *hru_tmin;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classfrozen* klone(string name) const;
};

class ClassNetroute : public ClassModule {
public:

ClassNetroute(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

long meltrunoffDiv;
long soil_ssrDiv;
long soil_runoffDiv;
long soil_gwDiv;

// declared variables
float *inflow;        // [nhru]
float *cuminflow;     // [nhru]
float *outflow;       // [nhru]
float *outflow_diverted; // [nhru]
float *cumoutflow_diverted; // [nhru]
float *cumoutflow;    // [nhru]
float *gwinflow;        // [nhru]
float *gwoutflow_diverted; // [nhru]
float *gwcumoutflow_diverted; // [nhru]

float *ssrinflow;        // [nhru]
float *ssrcuminflow;     // [nhru]
float *ssroutflow;       // [nhru]
float *ssrcumoutflow;    // [nhru]

float *runinflow;        // [nhru]
float *runcuminflow;     // [nhru]
float *runoutflow;       // [nhru]
float *runcumoutflow;    // [nhru]

float *gwoutflow;       // [nhru]
float *gwcuminflow;    // [nhru]
float *gwcumoutflow;    // [nhru]

float *basinflow;     // [BASIN] all HRUs
float *basinflow_s;   // [BASIN] all HRUs
float *cumbasinflow;  // [BASIN] all HRUs
float *basingw;       // [BASIN} all HRUs
float *basingw_s;     // [BASIN} all HRUs
float *cumbasingw;    // [BASIN} all HRUs

float *soil_ssr_Buf;    // buffered
float *soil_runoff_Buf; // buffered
float *meltrunoff_Buf;  // buffered
float *soil_gw_Buf;     // buffered

float *cum_to_Sd;         // [nhru]
float *cum_to_soil_rechr; // [nhru]

ClassClark *hruDelay;
ClassClark *ssrDelay;
ClassClark *runDelay;
ClassClark *gwDelay;

// declared parameters
const float *Kstorage;         // [nhru]
const float *Lag;              // [nhru]
const float *ssrKstorage;      // [nhru]
const float *ssrLag;           // [nhru]
const float *runKstorage;      // [nhru]
const float *runLag;           // [nhru]
const float *gwKstorage;      // [nhru]
const float *gwLag;           // [nhru]

const float *basin_area;        // [BASIN]
const float *hru_area;          // [nhru]
const long  *whereto;           // [nhru]
const long  *order;             // [nhru]
const long  *gwwhereto;             // [nhru]
const float *Sdmax;             // [nhru]
const float *soil_rechr_max;    // [nhru]
const long  *Sd_ByPass;         // [nhru]
const long  *soil_rechr_ByPass; // [nhru]

// variable inputs
const float *soil_gw;   // [nhru]
const float *soil_ssr;    // [nhru]
const float *soil_runoff; // [nhru]

// variable puts
float *Sd;
float *soil_moist;
float *soil_rechr;

// local allocated arrays

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassNetroute* klone(string name) const;
};

class Classinterception : public ClassModule {
public:

Classinterception(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared observations
const float *Qsi;

// variable inputs
const float *hru_t;
const float *hru_snow;
const float *hru_rain;
const float *hru_u;
const float *hru_rh;

// declared variables
float *SI_Lo;
float *net_snow;
float *net_rain;
float *SI_Subl;
float *Cum_Subl;
float *Cum_net_snow;
float *v;

// declared parameters
const float *Sbar;
const float *LAI;
const float *k;
const float *velw;
const float *Ht;
const float *WidthJ;
const float *basin_area;
const float *hru_area;

// variable inputs

// local allocated arrays

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classinterception* klone(string name) const;
};

class ClassGreenAmpt : public ClassModule {
public:

ClassGreenAmpt(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};
// declared variables
float *infil;
float *cuminfil;
float *runoff;
float *cumrunoff;
float *snowinfil;
float *cumsnowinfil;
float *meltrunoff;
float *cummeltrunoff;

// local variables
float *k;
float *F0;
float *f0;
float *F1;
float *f1;
float *dthbot;
float *psidthbot;

// declared parameters
const float *basin_area; // [BASIN]
const float *hru_area;
const float *soil_moist_max;
const float *soil_moist_init;
const long  *soil_type;

// variable inputs
const float *net_rain;
const float *snowmelt;
float *soil_moist; // changed to PUT

// class allocated
float garain;      // precipitation/int
float intensity;   // precipitation/int converted to mm/h
float pond;        // mm

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassGreenAmpt* klone(string name) const;

void infiltrate(void);
void ponding(void);
void startponding(void);
void howmuch(float F0, float dt);

float calcf1(float F, float psidth);
};

class Classalbedoparam : public ClassModule {
public:

Classalbedoparam(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
float *Albedo;

// declared parameters
const float *Albedo_Value;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classalbedoparam* klone(string name) const;
};

class Classalbedoobs : public ClassModule {
public:

Classalbedoobs(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
float *Albedo;

// declared observation variables
const float *Albedo_obs;      // interval data

// declared parameters
const float *Albedo_Value;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classalbedoobs* klone(string name) const;
};

class ClassHtobs : public ClassModule {
public:

ClassHtobs(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
float *Ht_var;

// declared observation variables
const float *Ht_obs;      // interval data

// declared parameters
//const float *Ht;
float *Ht;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassHtobs* klone(string name) const;
};

class TSTEP_REC{ // time step information
  public:

#define	DATA_TSTEP	   0
#define	NORMAL_TSTEP	   1
#define	MEDIUM_TSTEP	   2
#define	SMALL_TSTEP	   3

// default for normal run timestep's threshold for a layer's mass (kg/m^2)

#define	DEFAULT_NORMAL_THRESHOLD  60.0

// default for medium run timestep's threshold for a layer's mass (kg/m^2)

#define	DEFAULT_MEDIUM_THRESHOLD  10.0

// default for small run timestep's threshold for a layer's mass (kg/m^2)

#define	DEFAULT_SMALL_THRESHOLD  1.0


  int level;	    // timestep's level

  long time_step;   // length of timestep (seconds)

  int intervals;    // # of these timestep that are in the previous-level's timestep (not used for level 0: data tstep)

  float threshold;  // mass threshold for a layer to use this timestep (not used for level 0: data tstep)

  TSTEP_REC() : level(0), time_step(24*3600/Global::Freq), intervals(1), threshold(0.0) {};

};

class  INPUT_REC{ // climate-data input records
  public:

  float S_n;	// net solar radiation (W/m^2)
  float I_lw;	// incoming longwave (thermal) rad (W/m^2)
  float T_a;	// air temp (C)
  float e_a;	// vapor pressure (Pa)
  float u;	// wind speed (m/sec)
  float T_g;	// soil temp at depth z_g (C)
  float F_g;	// soil flux at depth z_g (W/m^2)
};

class  PRECIP_REC{ // precip-data input records
  public:

  float	  m_pp;		// total precipitation mass (kg/m^2)
  float	  m_rain;	// mass of rain in precip   (kg/m^2)
  float	  m_snow;	// mass of snow in precip   (kg/m^2)
  float	  m_drift;	// mass of snow drift       (kg/m^2)
  float	  m_subl;	// mass of snow drift       (kg/m^2)
  float	  z_snow;	// depth of snow in precip  (m)
};

class ClassSnobalBase : public ClassModule {

    public:

    ClassSnobalBase(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables

//   snowpack information

    long*   layer_count;    // number of layers in snowcover: 0, 1, or 2
    float*  z_s;            // total snowcover thickness (m)
    float*  z_s_0;          // active layer depth (m)
    float*  z_s_l;          // lower layer depth (m)
    float*  rho;            // average snowcover density (kg/m^3)
    float*  m_s;            // snowcover's specific mass (kg/m^2). Init by init_snow.
    float*  m_s_0;          // active layer specific mass (kg/m^2). Init by init_snow.
    float*  m_s_l;          // lower layer specific mass (kg/m^2). Init by init_snow.
    float*  T_s;            // average snowcover temp (K). Init by init_snow
    float*  T_s_0;          // active snow layer temp (K)
    float*  T_s_l;          // lower layer temp (C)
    float*  cc_s;           // snowcover's cold content (J/m^2). Init by init_snow.
    float*  cc_s_0;         // active layer cold content (J/m^2). Init by init_snow.
    float*  cc_s_l;         // lower layer cold content (J/m^2). Init by init_snow.
    float*  h2o_sat;        // % of liquid H2O saturation (relative water content, i.e., ratio of water in snowcover
//                                 to water that snowcover could hold at saturation)
    float*  h2o_vol;        // liquid h2o content as volume ratio: V_water/(V_snow - V_ice) (unitless).init_snow
    float*  h2o;            // liquid h2o content as specific mass(kg/m^2)
    float*  h2o_max;        // max liquid h2o content as specific mass(kg/m^2)
    float*  h2o_total;      // total liquid h2o: includes h2o in snowcover, melt, and rainfall (kg/m^2)

//   energy balance info for current timestep

    float  *R_n;            // net allwave radiation (W/m^2)
    float  *H;              // sensible heat xfr (W/m^2)
    float  *L_v_E;          // latent heat xfr (W/m^2)
    float  *G;              // heat xfr by conduction & diffusion from soil to snowcover (W/m^2)
    float  *G_0;            // heat xfr by conduction & diffusion from soil or lower layer to active layer (W/m^2)
    float  *M;              // advected heat from precip (W/m^2)
    float  *delta_Q;        // change in snowcover's energy (W/m^2)
    float  *delta_Q_0;      // change in active layer's energy (W/m^2)

//   mass balance vars for current timestep

    float  *melt_direct_int;       // specific melt (kg/m^2 or m)
    float  *sum;       // specific melt (kg/m^2 or m)
    float  *E_int;	    // mass flux by evap into air from active layer (kg/m^2/s)
    float  *E_s_int;	    // mass of evap into air & soil from snowcover (kg/m^2)
    float  *snowmelt_int;   // predicted specific runoff (m/sec)
    float  *snowmeltD;      // daily predicted specific runoff (m/sec)

//   mass balance vars for variable timestep

    float  *melt;        // specific melt (kg/m^2 or m)
    float  *E;		 // mass flux by evap into air from active layer (kg/m^2/s)
    float  *E_s;	 // mass of evap into air & soil from snowcover (kg/m^2)
    float  *ro_predict;  // predicted specific runoff (m/sec)

    float  *E_s_0;        // mass of evaporation to air (kg/m^2)
    float  *E_s_l;        // mass of evaporation to soil (kg/m^2)
    float  *E_l;	  // mass flux by evap/cond to soil (kg/m^2/s)

    float  *E_s_0_int;        // mass of evaporation to air (kg/m^2)
    float  *E_s_l_int;        // mass of evaporation to soil (kg/m^2)
    float  *E_l_int;	  // mass flux by evap/cond to soil (kg/m^2/s)

//   precipitation info adjusted for current run timestep

    float  *m_precip;	// specific mass of total precip (kg/m^2)
    float  *m_rain;	// specific mass of rain in precip (kg/m^2)
    float  *m_snow;	// specific mass in snow in precip (kg/m^2)
    float  *m_drift;	// specific mass in snow drift (kg/m^2)
    float  *m_subl;	// specific mass in snow sublimation (kg/m^2)
    float  *rho_snow;   // density of snowfall (kg/m^3)
    float  *T_pp;       // precip temp (K)
    float  *z_snow;	// depth of snow in precip (m)

//   precipitation info for the current DATA timestep

    long   *precip_now;	// precipitation occur for current timestep?
    float  *T_rain;	// rain's temp (K)
    float  *T_snow;	// snowfall's temp (K)
    float  *h2o_sat_snow; // snowfall's % of liquid H2O saturation

//   local climate-data values for the current run timestep
    float  *S_n;      // net solar radiation (W/m^2)
    float  *I_lw;     // incoming longwave (thermal) rad (W/m^2)
    float  *T_a;      // air temp (K)
    float  *e_a;      // vapor pressure (Pa)
    float  *u;        // wind speed (m/sec)
    float  *T_g;      // soil temp at depth z_g (C)
    float  *F_g;      // soil flux at depth z_g (W/m^2)

    long *isothermal; // melting?
    long *snowcover;  // snow on gnd at start of current timestep?
    long  *stop_no_snow;       //

//   local variables
    float  *P_a;            // air pressure (Pa)
    float  *m_precip_cum;   //
    float  *m_rain_cum;     //
    float  *m_snow_cum;     //
    float  *m_drift_cum;    //
    float  *m_subl_cum;    //
    float  *E_s_cum;        //
    float  *cumsnowmelt;    //
    float  *melt_direct_cum;       //
    float  *Fault;       //

// debug variables
/*    float *Length;
    float **Length_array;
    float *Ustar;
    float **Ustar_array;
    float *e;
    float **e_array;
    float *h;
    float **h_array;
    long *ier;
    long **ier_array;
    long  *ArrayCnt; */

// declared parameters

//   measurement heights/depths

    const float *hru_elev;    // HRU elevation
    const float *basin_area;  // [BASIN]
    const float *hru_area;
    const float *KT_sand; // thermal conductivity of wet sand

    const long *relative_hts; // TRUE if measurements heights, z_T and z_u, are relative to snow surface
                                // FALSE if they are absolute heights above the ground
    const float  *T_g_or_G_flux;    // soil temp or ground flux option
    const float *z_g;         // depth of soil temp meas (m)
    const float *z_u;         // height of wind measurement (m)
    const float *z_T;         // height of air temp & vapor pressure measurement (m)
    const float *z_0;         // roughness length
    const float *max_z_s_0;   // maximum active layer thickness (m)
    const float *max_h2o_vol; // max liquid h2o content as volume ratio: V_water/(V_snow - V_ice) (unitless)

//    void decl(void);

  void init(void);

//    void run(void);

  void finish(bool good); // delete local storage used

  void init_snow(void);

  void _calc_layers(void);

  void _layer_mass(void);

  float _cold_content(float	temp, float	mass); // temperature of layer specific mass of layer

  void do_data_tstep(void);

  int _divide_tstep(TSTEP_REC *tstep); // record of timestep to be divided

  int _below_thold(float threshold);	 // current timestep's threshold for a layer's mass

  int _do_tstep(TSTEP_REC *tstep); // timestep's record

  int _e_bal(void);

  void _net_rad(void);

  int _h_le(void);

  float g_soil(
  float	rho,	// snow layer's density (kg/m^3)
  float	tsno,	// snow layer's temperature (K)
  float	tg,	// soil temperature (K)
  float	ds,	// snow layer's thickness (m)
  float	dg,	// dpeth of soil temperature measurement (m)
  float	pa);	// air pressure (Pa)

  float g_snow(
  float	rho1,	// upper snow layer's density (kg/m^3)
  float	rho2,	// lower  "     "        "    (kg/m^3)
  float	ts1,	// upper snow layer's temperature (K)
  float	ts2,	// lower  "     "         "       (K)
  float	ds1,	// upper snow layer's thickness (m)
  float	ds2,	// lower  "     "         "     (m)
  float	pa);	// air pressure (Pa)

  void _advec(void);

  void _mass_bal(void);

  void _time_compact(void);

  void _precip(void);

  void _snowmelt(void);

  void _drift(void);

  void _new_density(void);

  void _adj_snow(float delta_z_s, float delta_m_s); // change in snowcover's depth change is snowcover's mass

  void _evap_cond(void);

  void _h2o_compact(void);

  void _adj_layers(void);

  void _runoff(void);

  float new_tsno(float spm, float t0, float ccon);

  float heat_stor(float cp, float spm, float tdif);

  float sati(float tk);

  float ssxfr(float  k1, float  k2, float  t1, float  t2, float  d1, float  d2);

  float efcon(float k, float t, float p);

  int hle1(float press, float ta, float ts, float za, float ea, float es, float zq, float u, float zu,
                   float z0, float &h, float &le, float &e);

// time step information

  TSTEP_REC  **tstep_info; 	// array of info for each timestep [nhru] [4]:
                                //           0 : data timestep
                                //           1 : normal run timestep
                                //           2 : medium  "     "
                                //           3 : small   "     "

  long *time_step;     // length current timestep (sec)
  long *current_time;  // start time of current time step (sec)

// climate-data input records

  INPUT_REC  *input_rec1;	// input data for start of data timestep [nhru]
  INPUT_REC  *input_rec2;	//   "     "   "  end   "   "      "     [nhru]

  INPUT_REC **input_deltas;	// deltas for climate-input parameters
                                //  over each timestep [nhru] [4]

  PRECIP_REC **precip_info;	// array of precip info adjusted for
                                //  each timestep [nhru] [4]

  int **computed;		// array of flags for each timestep;
                                //  TRUE if computed values for input
                                //   deltas and precip arrays [nhru] [4]
};

class ClassSnobalX : public ClassSnobalBase {

    public:

    ClassSnobalX(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassSnobalBase(Name, Version, Lvl) {};

    ClassSnobalX* klone(string name) const;

// variable climate-data inputs

    const float  *S_n_X;      // net solar radiation (W/m^2)
    const float  *I_lw_X;     // incoming longwave (thermal) rad (W/m^2)
    const float  *T_a_X;      // air temp (C)
    const float  *e_a_X;      // vapor pressure (Pa)
    const float  *u_X;        // wind speed (m/sec)
    const float  *T_g_X;      // soil temp at depth z_g (C)
    const float  *F_g_X;      // soil flux at depth z_g ()

// variable precipitation inputs

    const float  *m_precip_X;	// specific mass of total precip     (kg/m^2)
    const float  *m_rain_X;	// specific mass of rain in precip   (kg/m^2)
    const float  *m_snow_X;	// specific mass in snow in precip   (kg/m^2)
    const float  *m_drift_X;	// specific mass in snow drift       (kg/m^2)
    const float  *m_subl_X;	// specific mass of snow sublimation (kg/m^2)
    const float  *rho_snow_X;   // density of snowfall               (kg/m^3)
    const float  *T_pp_X;       // precip temp (C)


    void decl(void);

    void init(void);

    void run(void);

    void finish(bool good); // delete local storage used
};

class ClasspbsmSnobal : public ClassModule {
public:

ClasspbsmSnobal(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 1001), // setting PeerRank
                                  hru_basin(NULL) {};
float hru_u_;

// declared variables
float *Subl;
float *Drift;     // HRU composite drift
float *Drift_out; // HRU drift out
float *Drift_in;  // HRU drift in
float *cumSubl;
float *cumDrift;
float *cumDriftIn;
float *Prob;
float *snowdepth;
float *BasinSnowLoss;
float *cumBasinSnowLoss;
float *cumBasinSnowGain;
float *SnowAge;
long  *DrySnow;

// declared parameters
const float *fetch;
const float *Ht;
const float *distrib;
const float *basin_area;
const float *hru_area;
const float *A_S;
const float *N_S;
const long *inhibit_evap;
const long *inhibit_bs;
const long *inhibit_subl;

// variable inputs
const float *hru_t;
const float *hru_ea;
const float *hru_u;
const float *hru_Uadjust;
const float *net_snow;

// put variable inputs
float *SWE; // actually m_s
float *z_s;
float *rho;

// local allocated arrays
float *hru_basin;


void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClasspbsmSnobal* klone(string name) const;

};

class ClassalbedoRichard : public ClassModule {
public:

ClassalbedoRichard(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// local class

    float dt;

// declared variables
float *Albedo;

// put variables:

 float *net_snow;
 float *SWE;

// get variables:

const float *T0;

// declared parameters
  const float *Albedo_Bare;
  const float *Albedo_Snow;
  const float *a1;       // Albedo decay time constant for cold snow (s)
  const float *a2;       // Albedo decay time constant for melting snow (s)
  const float *amin;     // Minimum albedo for aged snow
  const float *amax;     // Maximum albedo for fresh snow
  const float *smin;     // Minimum snowfall to refresh snow albedo (mm)

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassalbedoRichard* klone(string name) const;
};

class ClassalbedoBaker : public ClassModule {
public:

ClassalbedoBaker(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
  float *Albedo;
  float *Ab_t;

// get variables:

// put variables:

  float *net_snow;
  float *SWE;

// declared parameters
  const float *Albedo_Bare;
  const float *Albedo_Snow;
  const float *refresh;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassalbedoBaker* klone(string name) const;
};

class ClassHMSA : public ClassModule {
public:

ClassHMSA(string Name = "HMSA", String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl){};

float Soil_Temp;

long MaxFrontCnt;
long Liqcnt;
long Totcnt;

// declared observation variables
const float *Tsurf_obs;
const float *LiqWat;
const float *TotMoist;

// variable inputs
const float *Tsurf_var;

//const float *theta;

// declared variables
float *Cum_Thaw;
float *Cum_Frozen;
float *Lamda_b;
float *Frozen_D;
float *Thaw_D;
float *Last_Tsurf;

float *C_K0;
float *Total_Moisture;
float **Total_Moisture_lay;
float *Cum_d;
float **Cum_d_lay;
long *Frozen_ID;
long **Frozen_ID_lay;
float *FrntDepth;
float **FrntDepth_array;
float *ThawCum;
float **ThawCum_array;
float *FreezeCum;
float **FreezeCum_array;
long *FrntDepthType;
long **FrntDepthType_array;
long *FrontCnt;

// local
float *Tsurface;

// declared parameters
const float *Alpha_T;
const float *Alpha_F;
const float *d_lay;
const float *BulkDensityLayer;
const float *InitThaw_D;
const float *InitFrozen_D;
const float *D_Top;
const float *TMPB_W;
const float **TMPB_W_NDEF;
const long *Alpha_ID;
const long *Soil_ID;
const long **Soil_ID_lay;

const float *Soil_Depths;
const float **Soil_depths_lay; // [nn][hh]
const float *Organic;
const float **Organic_lay; // [nn][hh]
const float *Porosity;
const float **Porosity_lay; // [nn][hh
const float *BulkDensity;
const float **BulkDensity_lay; // [nn][hh]
float *f;
float **f_lay;
float *Soil_Ice;
float **Soil_Ice_lay;
float *Soil_Water;
float **Soil_Water_lay;

const long *Soil_Layers;
const long *Method_ID;

void decl(void);
void init(void);
void run(void);
void Get_Heat_Param_Soil(float Soil_temp, long nn);
void Get_Heat_Chad(long nn);

ClassHMSA* klone(string name) const;
};

float Farouki_a(float fract_por);

class Classqdrift : public ClassModule {
public:

Classqdrift(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

ClassClark *Delaymelt;

// declared observation variables
const float *p;

// declared variables
float *SWE;
float *driftmelt;
float *driftmeltDly;
float *cumdriftmelt;
float *cumdriftmeltDly;
float *driftmeltD;
float *cump;

// declared parameters
const long *Type;      // NOTUSED, DRIFT or HUMMOCK
const long *DrainTo;   // drain to HRU
const float *InitSWE;  // initial SWE
const float *length;   // length normal to creek
const float *meltstorage;  // delay parameter (days)
const float *meltLag;      // delay parameter (days)
const float *catchadjust;  // rain fall calibration

// variable inputs
const float *Qm;

// local allocated arrays

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classqdrift* klone(string name) const;
};

class Classwalmsley_wind : public ClassModule {
public:
Classwalmsley_wind(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
float *hru_Uadjust;
float *hru_Uchange;
float *WR;

// declared parameters
const float *Zwind;
const float *Ax;
const float *Bx;
const float *L;
const float *Walmsley_Ht;

// varaible inputs
const float *hru_u;

void decl(void);
void init(void);
void run(void);

Classwalmsley_wind* klone(string name) const;
};

class ClassNetroute_M : public ClassModule {
public:

ClassNetroute_M(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

long meltrunoffDiv;
long soil_ssrDiv;
long soil_runoffDiv;
long soil_gwDiv;

// declared variables
float *inflow;        // [nhru]
float *cuminflow;     // [nhru]
float *outflow;       // [nhru]
float *outflow_diverted; // [nhru]
float *cumoutflow_diverted; // [nhru]
float *cumoutflow;    // [nhru]
float *gwinflow;        // [nhru]

float *ssrinflow;        // [nhru]
float *ssrcuminflow;     // [nhru]
float *ssroutflow;       // [nhru]
float *ssrcumoutflow;    // [nhru]

float *runinflow;        // [nhru]
float *runcuminflow;     // [nhru]
float *runoutflow;       // [nhru]
float *runcumoutflow;    // [nhru]

float *gwoutflow;       // [nhru]
float *gwoutflow_diverted; // [nhru]
float *gwcuminflow;     // [nhru]
float *gwcumoutflow;    // [nhru]
float *gwcumoutflow_diverted; // [nhru]

float *basinflow;     // [BASIN] all HRUs
float *basinflow_s;   // [BASIN] all HRUs
float *cumbasinflow;  // [BASIN] all HRUs
float *basingw;       // [BASIN} all HRUs
float *basingw_s;     // [BASIN} all HRUs
float *cumbasingw;    // [BASIN} all HRUs

float *soil_ssr_Buf;    // buffered
float *soil_runoff_Buf; // buffered
float *meltrunoff_Buf;  // buffered
float *soil_gw_Buf;     // buffered

float *cum_to_Sd;         // [nhru]
float *cum_to_soil_rechr; // [nhru]

float *Kstorage;         // [nhru] Muskingum

ClassMuskingum *hruDelay;
ClassClark *ssrDelay;
ClassClark *runDelay;
ClassClark *gwDelay;

// declared parameters
const float *route_n;         // [nhru]
const float *route_R;         // [nhru]
const float *route_S0;        // [nhru]
const float *route_L;         // [nhru]
const float *route_X_M;       // [nhru]
const long  *route_Cshp;      // [nhru]

const float *Lag;              // [nhru]
const float *ssrKstorage;      // [nhru]
const float *ssrLag;           // [nhru]
const float *runKstorage;      // [nhru]
const float *runLag;           // [nhru]
const float *gwKstorage;       // [nhru]
const float *gwLag;            // [nhru]

const float *basin_area;        // [BASIN]
const float *hru_area;          // [nhru]
const long  *whereto;           // [nhru]
const long  *gwwhereto;         // [nhru]
const long  *order;             // [nhru]
const float *Sdmax;             // [nhru]
const float *soil_rechr_max;    // [nhru]
const long  *Sd_ByPass;         // [nhru]
const long  *soil_rechr_ByPass; // [nhru]

// variable inputs
const float *soil_gw;     // [nhru]
const float *soil_ssr;    // [nhru]
const float *soil_runoff; // [nhru]

// variable puts
float *Sd;
float *soil_moist;
float *soil_rechr;

// local allocated arrays

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassNetroute_M* klone(string name) const;
};

class ClassREWroute : public ClassModule {
public:

ClassREWroute(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 9999) {};

long inflowCnt;
long gwCnt;

// declared variables
float *rew;
float *gwrew;

float **inflow_All;
float **gw_All;

float *inflow;        // [nhru]
float *cuminflow;     // [nhru]
float *outflow;       // [nhru]
float *cumoutflow;    // [nhru]

float *gwinflow;        // [nhru]
float *cumgwinflow;     // [nhru]
float *gwoutflow;       // [nhru]
float *cumgwoutflow;    // [nhru]

float *flow;     // [BASIN] all HRUs
float *flow_s;   // [BASIN] all HRUs
float *cumflow;  // [BASIN] all HRUs

float *gwflow;     // [BASIN] all HRUs
float *gwflow_s;   // [BASIN] all HRUs
float *cumgwflow;  // [BASIN] all HRUs

float *WS_Kstorage_var;         // [nhru]
float *WS_gwKstorage_var;         // [nhru]

ClassMuskingum *inflowDelay;
ClassMuskingum *gwDelay;

ClassClark *Clark_inflowDelay;
ClassClark *Clark_gwDelay;

// declared parameters

const float *watershed_area;      // [watershed area (basin)]
const float *RB_area;        // [RBs (nhru)]

const float *WS_route_n;         // [nhru]
const float *WS_route_R;         // [nhru]
const float *WS_route_S0;        // [nhru]
const float *WS_route_L;         // [nhru]
const long  *WS_Channel_shp;      // [nhru]

const float *WS_Lag;             // [nhru]
const float *WS_route_X_M;       // [nhru]
const long  *WS_whereto;         // [nhru]
const long  *WS_order;           // [nhru]

const float *WS_gwLag;           // [nhru]
const float *WS_gwroute_X_M;     // [nhru]
const long  *WS_gwwhereto;       // [nhru]
const long  *WS_gworder;         // [nhru]

const float *WS_Kstorage;     // [nhru]
const float *WS_gwKstorage;   // [nhru]

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassREWroute* klone(string name) const;
};

class ClassMSM : public ClassModule {

    public:

    ClassMSM(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 2000) {};

// declared observation variables

    const float *Qsi;  // Downward shortwave radiation (W/m2)
    const float *Qli;  // Downward longwave radiation (W/m2)

// variable puts
    float *SWE;  // (kg/m2)

// variable inputs
    const float *hru_snow;  // (kg/m2)
    const float *hru_t;  //
    const float *hru_u;  //
    const float *hru_ea;  //
    const float *hru_rh;  //

// declared variables

    float *alb;         // Snow albedo
    float *snowmelt;    // (kg/m2)
    float *snowmeltD;   // (kg/m2)
    float *cumsnowmelt; // (kg/m2)
    float *sursubl;     // (kg/m2)
    float *cumsursubl;  // (kg/m2)
    float *T0;          // Surface temperature (�K)
    float *Pa;          // Average surface pressure (KPa)

    float *LE;   // Latent heat flux (W/m^2)
    float *H;    // Sensible heat flux (W/m^2)
    float *Hsm;  // Snowmelt heat flux (W/m^2)
    float *LWn;  // Net longwave radiation (W/m^2)
    float *SWn;  // Net shortwave radiation (W/m^2)

// declared parameters

    const float *a1;       // Albedo decay time constant for cold snow (s)
    const float *a2;       // Albedo decay time constant for melting snow (s)
    const float *amin;     // Minimum albedo for aged snow
    const float *amax;     // Maximum albedo for fresh snow
    const float *smin;     // Minimum snowfall to refresh snow albedo (mm)
    const float *Ht;       // vegetation height
    const float *Zref;     // Reference height
    const float *hru_elev; // Average surface pressure (KPa)
    const float *Z0snow;   // snow roughness length (m)
    const float *basin_area;   // [BASIN]
    const float *hru_area;

// variable inputs

    void decl(void);

    void init(void);

    void run(void);

    void finish(bool good);

    ClassMSM* klone(string name) const;

    void EXCH(long hh, float Q1, float U1, float &CH);

    void ALBEDO(long hh);

    void SURF(long hh, float Q1, float U1);

// local class

    float dt;
};

class Classqmelt2 : public ClassModule {
public:

Classqmelt2(string Name = "Qmelt", String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl){};

// declared variables
float *Qm;      // MJ/m2/Int
float *Qg;      // MJ/m2/Int
float *cum_Qm;  // MJ/m2
float *cum_Qg;  // MJ/m2
float *QmD;     // MJ/m2
float *QgD;     // MJ/m2

// input variables
const float *tmean;  // �C

// declared parameters
const float *TIa0Mn;
const float *TIa1Mn;
const float *TIs0Mn;
const float *TIs1Mn;

// declared observations
const float *t;      // �C
const float *ts;     // �C

// declared observation functions
float *tpos;   // �C
float *tsmean; // �C
float *tspos;  // �C

void decl(void);
void init(void);
void run(void);

Classqmelt2* klone(string name) const;
};

class Classquinton2 : public ClassModule {
public:

Classquinton2(string Name = "Quinton", String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl){};

ClassClark *Delayrunoff;
ClassClark *Delayflow;

// declared observation variables
const float *p;

// input variables
const float *Qg;        // MJ/m2
const float *driftmelt; // melt depth from upstream drift

// declared parameters
//const long *k_range;        // normal, high or low
const long *DrainTo;        // drain to HRU
const long *DriftDrainTo;   // drain to HRU
const float *slope;         // (m/m)
const float *length;        // length normal to creek
const float *Kbtm;         // bottom hydraulic conductivity (m/d)
const float *Ktop;         // bottom hydraulic conductivity (m/d)
const float *ztrn;         // transition depth (m)
const float *Residual;      // Organic non-drainable porosity ()
const float **Residual_lay; // Organic non-drainable porosity ()
const float *n_const;       // Van Genutchen constant
const float **n_const_lay;  // Van Genutchen constant
const float *a_const;       // Van Genutchen constant
const float **a_const_lay;  // Van Genutchen constant
const float *Drained;       // depth of surface drained organic material (m)
const float *FrozenTo;      // initial depth of frost table (m)
const float *runoffstorage; // runoff parameter ()
const float *runoffLag;     // runoff parameter ()
const float *flowstorage;   // flow parameter ()
const float *flowLag;       // flow parameter ()
const float *catchadjust_mult;   // rain fall calibration

const float *d;             // depth of layer  (m)
const float **d_lay;        // depth of layer  (m)
const float *Pors;          // filler only gives first value
const float **Pors_def;     // array of all values
const long  *soil_type;
const long  **soil_type_lay;
const float *tinit;         // initial layer temperature (�C)
const float **tinit_lay;    // initial layer temperature (�C)

// declared variables
float *Depth;          // hydraulic conductivity (m/day)
float *k;              // hydraulic conductivity (m/day)
float *d_surface;      // debug
float *watertable;     // water table depth (m)
float *dmelt;          // melt depth (m)
float *flowin;         // flowin depth (m/m2)
float *flowinm3;       // flowin depth (m3)
float *cumflowin;      // cumulative flowin depth (m)
float *runoff;         // runoff ((m/m2)/int)
float *runoffDly;      // runoff ((m/m2)/int)
float *runoffm3Dly;    // runoff (m3/int)
float *cumrunoff;      // cumulative runoff (m)
float *flow;           // total flow (m/int)
float *flowDly;        // total flow (m/int)
float *flowm3Dly;      // total flow (m3/int)
float *cumflow;        // cumulative total flow from all layers(m3/s)
float *cump;           // cumulative precipitation
float *loss;           // total loss (m/int)
float *transit;        // transit time through HRU (hr)
float *theta;          // soil moisture (m3/m3)
float **theta_lay;     // soil moisture (m3/m3)
float *layerwater;      // thawed water depth in layer (m)
float **layerwater_lay; // thawed water depth in layer (m)
float *capillary;      // locked thawed water depth in layer (m)
float **capillary_lay; // locked thawed water depth in layer (m)
float *tension;        // capillary tension (m)
float **tension_lay;   // capillary tension (m)
float *wDrained;       // working depth of surface drained organic material (m)

float *Cvis;         // frozen/saturated
float **Cvis_lay;    // heat capacity (J/m3/K)

float *Cvisa;       // frozen/unsaturated
float **Cvisa_lay;  // heat capacity (J/m3/K)

float *Cvws;        // unfrozen/saturated
float **Cvws_lay;   // heat capacity (J/m3/K)

float *Cvwsa;       // unfrozen/unsaturated
float **Cvwsa_lay;  // heat capacity (J/m3/K)

float *lamis;       // frozen/saturated
float **lamis_lay;  // thermal conductivity (W/m/K)

float *lamws;       // unfrozen/saturated
float **lamws_lay;  // thermal conductivity (W/m/K)

float *lamwsa;      // unfrozen/unsaturated
float **lamwsa_lay; // thermal conductivity (W/m/K)

float *tlayer;         // layer temperature (�C)
float **tlayer_lay;    // layer temperature (�C)

// local constants

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classquinton2* klone(string name) const;
};

float Farouki_a(float fract_por);

class Classqdrift2 : public ClassModule {
public:

Classqdrift2(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

ClassClark *Delaymelt;

// declared observation variables
const float *p;

// declared variables
float *SWE;
float *driftmelt;
float *driftmeltDly;
float *cumdriftmelt;
float *cumdriftmeltDly;
float *driftmeltD;
float *cump;

// declared parameters
const float *InitSWE;  // initial SWE
const float *length;   // length normal to creek
const float *meltstorage;  // delay parameter (days)
const float *meltLag;      // delay parameter (days)
const float *catchadjust_mult;  // rain fall calibration

// variable inputs
const float *Qm;

// local allocated arrays

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classqdrift2* klone(string name) const;
};

class ClassLongVt : public ClassModule {
public:

ClassLongVt(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared observation variables
  const float *Qsi;
  const float *QsiD;

// declared observation functions
  float *QsiDavg;

// declared observations
  float *Qli;

// declared variables
  float *Qli_Var;
  float *QliVt_Var;
  float *tau;

// declared parameters
  const float *Vt;

//  const float *epsilon_clear;
  const float *epsilon_s;

// variable inputs
  const float *hru_t;
  const float *hru_ea;
  const float *hru_rh;
  const float *QdroDext;
  const float *QsiD_Var;

void decl(void);
void init(void);
void run(void);

ClassLongVt* klone(string name) const;
};

class Classpbsm_M : public ClassModule {
public:

Classpbsm_M(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 1001), // setting PeerRank
                                  hru_basin(NULL) {};
// declared variables
float *SWE;
float *Subl;
float *Drift;
float *cumSubl;
float *cumDrift;
float *cumDriftIn;
float *cumSno;
float *Prob;
float *snowdepth;
float *BasinSnowLoss;
float *cumBasinSnowLoss;
float *cumBasinSnowGain;
float *SnowAge;
float *this_distrib;
float *Results;
float **Results_lay;
float *Q_leeslope;
float *Q_valley;
long  *DrySnow;

// declared parameters
const float *fetch;
const float *Ht;
const float *hru_Ht;
const float *distrib;
const float **distrib_hru;
const float *basin_area;
const float *hru_area;
const float *A_S;
const float *N_S;
const float *Zwind;
const float *hru_GSL;
const float *Beta_M;
const long *inhibit_evap;
const long *inhibit_bs;
const long *inhibit_subl;
const long *eq_prof;

// variable inputs
const float *hru_t;
const float *hru_rh;
const float *hru_u;
const float *net_snow;
const long  *hru_newsnow;

// local allocated arrays
float *hru_basin;


void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classpbsm_M* klone(string name) const;
void Sum(float TQsalt, float TQsusp, float SBsum, float SBsalt, float & DriftH, float & SublH);
void Pbsm(float E_StubHt, float Uthr, float & DriftH, float & SublH, float t, float u, float rh, float Fetch,
            long N_S, float A_S, float GSL, float height, float Beta_M, float & Qdist_leeslope, float & Qdist_valley);
};

class ClassNetroute_D : public ClassModule {
public:

ClassNetroute_D(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

long meltrunoffDiv;
long soil_ssrDiv;
long soil_runoffDiv;
long soil_gwDiv;

// declared variables
float *inflow;           // [nhru]
float *cuminflow;        // [nhru]
float *outflow;          // [nhru]
float *outflow_diverted; // [nhru]
float *cumoutflow_diverted; // [nhru]
float *cumoutflow;       // [nhru]
float *cumscaling_boost; // [nhru]
float *gwinflow;         // [nhru]
float *gwoutflow_diverted; // [nhru]
float *gwcumoutflow_diverted; // [nhru]

float *ssrinflow;        // [nhru]
float *ssrcuminflow;     // [nhru]
float *ssroutflow;       // [nhru]
float *ssrcumoutflow;    // [nhru]

float *runinflow;        // [nhru]
float *runcuminflow;     // [nhru]
float *runoutflow;       // [nhru]
float *runcumoutflow;    // [nhru]

float *gwoutflow;       // [nhru]
float *gwcuminflow;    // [nhru]
float *gwcumoutflow;    // [nhru]

float *basinflow;     // [BASIN] all HRUs
float *basinflow_s;   // [BASIN] all HRUs
float *cumbasinflow;  // [BASIN] all HRUs
float *basingw;       // [BASIN} all HRUs
float *basingw_s;     // [BASIN} all HRUs
float *cumbasingw;    // [BASIN} all HRUs

float *soil_ssr_Buf;    // buffered
float *soil_runoff_Buf; // buffered
float *meltrunoff_Buf;  // buffered
float *soil_gw_Buf;     // buffered

float *cum_to_Sd;         // [nhru]
float *cum_to_soil_rechr; // [nhru]

float *distrib_sum;

ClassClark *hruDelay;
ClassClark *ssrDelay;
ClassClark *runDelay;
ClassClark *gwDelay;

// declared parameters
const float *Kstorage;         // [nhru]
const float *Lag;              // [nhru]
const float *ssrKstorage;      // [nhru]
const float *ssrLag;           // [nhru]
const float *runKstorage;      // [nhru]
const float *runLag;           // [nhru]
const float *gwKstorage;       // [nhru]
const float *gwLag;            // [nhru]
const long  *gwwhereto;        // [nhru]

const float *basin_area;        // [BASIN]
const float *hru_area;          // [nhru]
const float *distrib;
const float *distrib_Basin;
const float **distrib_hru;
const float *Sdmax;             // [nhru]
const float *soil_rechr_max;    // [nhru]
const long  *Sd_ByPass;         // [nhru]
const long  *soil_rechr_ByPass; // [nhru]

const float *scaling_factor;    // temporary modification

// variable inputs
const float *soil_gw;   // [nhru]
const float *soil_ssr;    // [nhru]
const float *soil_runoff; // [nhru]

// variable puts
float *Sd;
float *soil_moist;
float *soil_rechr;

// local allocated arrays

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassNetroute_D* klone(string name) const;
};

class ClassNetroute_M_D : public ClassModule {
public:

ClassNetroute_M_D(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

long meltrunoffDiv;
long soil_ssrDiv;
long soil_runoffDiv;
long soil_gwDiv;

// declared variables
float *inflow;        // [nhru]
float *cuminflow;     // [nhru]
float *outflow;       // [nhru]
float *outflow_diverted;    // [nhru]
float *cumoutflow_diverted; // [nhru]
float *cumoutflow;    // [nhru]
float *cumscaling_boost;    // [nhru]
float *gwinflow;         // [nhru]
float *gwoutflow_diverted; // [nhru]
float *gwcumoutflow_diverted; // [nhru]

float *ssrinflow;        // [nhru]
float *ssrcuminflow;     // [nhru]
float *ssroutflow;       // [nhru]
float *ssrcumoutflow;    // [nhru]

float *runinflow;        // [nhru]
float *runcuminflow;     // [nhru]
float *runoutflow;       // [nhru]
float *runcumoutflow;    // [nhru]

float *gwoutflow;       // [nhru]
float *gwcuminflow;    // [nhru]
float *gwcumoutflow;    // [nhru]

float *basinflow;     // [BASIN] all HRUs
float *basinflow_s;   // [BASIN] all HRUs
float *cumbasinflow;  // [BASIN] all HRUs
float *basingw;       // [BASIN} all HRUs
float *basingw_s;     // [BASIN} all HRUs
float *cumbasingw;    // [BASIN} all HRUs

float *soil_ssr_Buf;    // buffered
float *soil_runoff_Buf; // buffered
float *meltrunoff_Buf;  // buffered
float *soil_gw_Buf;     // buffered

float *cum_to_Sd;         // [nhru]
float *cum_to_soil_rechr; // [nhru]

float *Kstorage;         // [nhru] Muskingum

float *distrib_sum;

ClassMuskingum *hruDelay;
ClassClark *ssrDelay;
ClassClark *runDelay;
ClassClark *gwDelay;

// declared parameters
const float *route_n;         // [nhru]
const float *route_R;         // [nhru]
const float *route_S0;        // [nhru]
const float *route_L;         // [nhru]
const float *route_X_M;       // [nhru]
const long  *route_Cshp;      // [nhru]

const float *Lag;             // [nhru]
const float *ssrKstorage;     // [nhru]
const float *ssrLag;          // [nhru]
const float *runKstorage;     // [nhru]
const float *runLag;          // [nhru]
const float *gwKstorage;      // [nhru]
const float *gwLag;           // [nhru]
const long  *gwwhereto;       // [nhru]

const float *basin_area;      // [BASIN]
const float *hru_area;        // [nhru]
const float *distrib;
const float *distrib_Basin;
const float **distrib_hru;
const float *Sdmax;           // [nhru]
const float *soil_rechr_max;  // [nhru]
const long  *Sd_ByPass;       // [nhru]
const long  *soil_rechr_ByPass; // [nhru]

const float *scaling_factor;    // temporary modification

// variable inputs
const float *soil_gw;   // [nhru]
const float *soil_ssr;    // [nhru]
const float *soil_runoff; // [nhru]

// variable puts
float *Sd;
float *soil_moist;
float *soil_rechr;

// local allocated arrays

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassNetroute_M_D* klone(string name) const;
};

class ClassSetSoil : public ClassModule {
public:

ClassSetSoil(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared parameters

const float *basin_area;   // [BASIN]
const float *hru_area;
const float *hru_lat;
const float *hru_elev;
const float *hru_GSL;
const float *hru_ASL;
const long *RUN_ID;
const long *RUN_START;
const long *RUN_END;

const float *soil_Depth;
const float *soil_Depth_rechr;
const float *Vol_h2o_content;
const float *soil_rechr_max;
const float *soil_rechr_init;
const float *soil_moist_max;
const float *soil_moist_init;

const long *soil_type;
const long *soiltype_rechr;

TStringList *basin_name;
TStringList *INIT_STATE;
TStringList *hru_names;

// declared variables
long *run_ID;

// variable inputs

void decl(void);
void init(void);

ClassSetSoil* klone(string name) const;
};

class ClassVolumetric : public ClassModule {
public:

ClassVolumetric(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 1001, "soil_gw") {}; // setting PeerVar. Cannot be "STATE" var

// declared parameters
const float *soil_Depth;
const float *fallstat;
const float *soil_moist_max;
const long *soil_type;
const long *set_fallstat;

// declared variables
float *Volumetric;
float *fallstat_V;

// variable inputs
const float *soil_moist;

void decl(void);
void init(void);
void run(void);

ClassVolumetric* klone(string name) const;
};

class ClassAnnan : public ClassModule {
public:

  float QsiDT, TauAT;

  ClassAnnan(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared observation variables
//const float *SunAct;

// declared variables
float *hru_SunAct;
float *QsiA_Var;
float *QsiD_Var;
float *QsiS_Var;

// declared parameters
const float *krs;
const float *hru_elev;

// declared observations
float *QsiA;
float *QsiD;
float *QsiS;

// variable inputs
const float *QdflatE;
const float *QdflatD;
const float *QdroDext;
const float *Qdro;
const float *Qdfo;
const float *QdfoD;
const float *SunMax;
const float *hru_tmax;
const float *hru_tmin;

void decl(void);
void init(void);
void run(void);

ClassAnnan* klone(string name) const;
};

class ClassHeating : public ClassModule {
public:

ClassHeating(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared observation variables
const float *Qsi;
const float *Qli;

float *QLin;

// declared parameters
const float *hru_lat;
const float *hru_elev;
const float *hru_GSL;
const float *hru_ASL;
const float *snow_alb;
const float *forest_alb;
const float *hd1;
const float *hd2;
const float *qt;
const float *w;
const float *L_B;
const float *L_T;
const float *LAI;

// variable inputs
const float *hru_t;
const float *hru_u;
const float *Ts;

// declared variables
float *Qnet_branch;
float *Qnet_trunk;
float *Lnet_branch;
float *Lnet_trunk;
float *Hnet_branch;
float *Hnet_trunk;
float *Wnet_branch;
float *Wnet_trunk;
float *T1_branch;
float *T1_trunk;
float *T2_branch;
float *T2_trunk;
float *T3_branch;
float *T3_trunk;
float *Temp_branch;
float *Temp_trunk;
float *Temp_forest;
float *H2_temp_branch;
float *H2_temp_trunk;
float *H2_temp_trans_branch;
float *H2_temp_trans_trunk;
float *Li;
float *dec;
float *SElev;
float *kt;
float *gcf;
float *Kd_slope;
float *Kb_slope;
float *Ko_slope;
float *opl_eff_slope;
float *Ksc_slope;
float *Knet_slope;
float *Nu_branch;
float *Nu_trunk;
float *BranchT_eff;
float *TrunkT_eff;
float *ForestT_eff;
float *Lin;
float *Lin_air;
float *Lnet;
float *Rnet;
float *v;
long  *Loops;

void decl(void);
void run(void);
void init(void);

ClassHeating* klone(string name) const;
};

class Classcalcsun : public ClassModule {
public:

Classcalcsun(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared observation variables
const float *Qsi;
const float *QsiD_Obs;
const float *SunAct;

// declared observation functions
float *Qsitot;

// declared variables
float *hru_SunAct;

// declared parameters

// variable inputs
const float *QdflatD;
const float *QdfoD;
const float *SunMax;
const float *QsiD_Var;

void decl(void);
void init(void);
void run(void);

Classcalcsun* klone(string name) const;
};

class ClassObstoPar : public ClassModule {
public:

long Ht_obsCnt;

ClassObstoPar(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
float *Ht_var;

// declared observation variables
const float *Ht_obs;      // interval data

// declared parameters
TStringList *obs_name;
TStringList *par_name;

float *Ht;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassObstoPar* klone(string name) const;
};

class ClassPrairieInfil : public ClassModule {
public:

ClassPrairieInfil(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl),
                                   Xinfil(NULL),
                                   timer(NULL) {};
// declared variables
float *snowinfil;
float *cumsnowinfil;
float *infil;
float *cuminfil;
float *meltrunoff;
float *cummeltrunoff;
float *runoff;
float *cumrunoff;
float *RainOnSnow;
float *RainOnSnowA;
long  *crackstat;
long  *crackon;

// declared parameters
const float *basin_area; // [BASIN]
const float *hru_area;
const float *fallstat;
const float *Major;      // threshold for major melt event(default is 5 mm/day)
const long  *PriorInfiltration;
const long  *texture;
const long  *groundcover;

// variable inputs
const float *hru_tmax;
const float *snowmelt;
const float *SWE;
const float *net_rain;

// local allocated arrays
float **Xinfil; // [3] [nhru]
long *timer;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassPrairieInfil* klone(string name) const;
};

class ClassCRHMCanopy:public ClassModule {

public:

ClassCRHMCanopy(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 2000) {};

float Qsi_, Qli_;

// observation variables

const float *Qsi;
const float *Qli;

// declared observation variables

float *Ts;
float *Qnsn;
float *Qsisn;
float *Qlisn;
float *Qlosn;

// put variables

float *SWE;

// declared variables

float *drip_Cpy;
float *thrufall_Cpy;
float *netRain_Cpy;
float *direct_rain;
float *rain_load;
float *Snow_load;
float *direct_snow;
float *SUnload;
float *Qnsn_Var;

float *net_rain;
float *cum_net_rain;
float *net_snow;
float *cum_net_snow;
float *net_p;
float *intcp_evap;
float *cum_intcp_evap;
float *Subl_Cpy;
float *cum_Subl_Cpy;

float *Cc;
float *k;
float *Tauc;
float *Pa;
float *ra;
float *u_FHt;
float *Pevap;

// variable inputs

const float *hru_t;
const float *hru_u;
const float *hru_rh;
const float *hru_ea;
const float *Albedo;

const float *hru_snow;
const float *hru_rain;
const float *hru_evap;

const float *SolAng;

const float *QsiS_Var;
const float *QsiA_Var;
const float *QliVt_Var;

// declared parameters:

const float *basin_area;   // [BASIN]
const float *hru_area;
const float *hru_elev;
const float *Ht;
const float *LAI;
const float *Sbar;
const float *Z0snow;
const float *Zref;
const float *Zwind;
const float *Zvent;
const float *unload_t;
const float *unload_t_water;

const long *inhibit_evap;


void decl(void);
void init(void);
void run(void);
void finish(bool good);

double delta(float t); // Slope of sat vap p vs t, kPa/�C
double gamma(float Pa, float t); // Psychrometric constant (kPa/�C)
float RHOa(float t, float ea, float Pa); // atmospheric density (kg/m^3)
float lambda(float t); // Latent heat of vaporization (mJ/(kg �C))

ClassCRHMCanopy* klone(string name) const;

};

class ClassPSPnew : public ClassModule {
public:

ClassPSPnew(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 2000) {};

// declared observation variables
const float *TsnowG;
const float *Lnot;

// declared variables
float *Qsubl;
float *Load;
float *Thru;
float *TCanSnow;
float *Tbiomass;

// declared parameters
const float *Sbar;
const float *LAI;
const float *Zcan;
const float *Zref;
const float *Ht;
const float *Biomass;
const float *k;
const float *HeightH;
const float *WidthJ;
const long *InitN;

// variable inputs
const float *RHref;
const float *Qn;
const float *QsIn;
const float *QsOut;
const float *hru_u;
const float *hru_p;
const float *TAref;
const float *SolarAng;

// local allocated arrays
float *T0CanSnow;
float *T0biomass;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

class ClassPSPnew* klone(string name) const;

};

class Classbrushintcp : public ClassModule {
public:

Classbrushintcp(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 2000) {};

// declared variables
float *net_rain;
float *cum_net_rain;
float *net_snow;
float *net_p;
float *Load;
float *Thru;
float *cumThru;
float *brushsubl;
float *spherecoeff;
float *cumbrushsubl;
float *intcp_evap;

// declared parameters
const float *basin_area;   // [ONE]
const float *hru_area;
const float *Ht;
const float *Zref;
const float *Zcan;
const float *brushAtten;
const float *Sbar;
const float *LAI;
const float *WidthJ;
const float *Tunload;

// variable inputs
const float *hru_t;
const float *hru_tmean;
const float *hru_rh;
const float *hru_u;
const float *hru_p;
const float *hru_rain;
const float *hru_snow;

// variable inputs/outputs
float *cumSubl;

// local allocated arrays

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classbrushintcp* klone(string name) const;

};

class ClassAyers : public ClassModule {
public:

ClassAyers(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
float *infil;
float *cuminfil;
float *runoff;
float *cumrunoff;
float *snowinfil;
float *cumsnowinfil;
float *meltrunoff;
float *cummeltrunoff;
float *melt; // interval melt - from snowmelD

// declared parameters
const float *basin_area; // [BASIN]
const float *hru_area;
const long  *texture;
const long  *groundcover;

// variable inputs
const float *net_rain;
const float *snowmeltD;

// local allocated arrays

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassAyers* klone(string name) const;
};

class ClassSnobalCRHM : public ClassSnobalBase {

    public:

    ClassSnobalCRHM(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassSnobalBase(Name, Version, Lvl) {};

    ClassSnobalCRHM* klone(string name) const;

    float Qsi_;
    float Qli_;

// Observations

    const float *Qsi; // incoming solar radiation (W/m^2)
    const float *Qli; // incoming longwave (thermal) rad (W/m^2) long
    const float *T_g_Obs; // ground temperature at depth
    const float *F_g_Obs; // ground flux at depth

// variable climate-data inputs

    const float  *T_a_X;      // air temp (C) hru_t
    const float  *T_pp_X;       // precip temp (C) hru_t
    const float  *e_a_X;      // vapor pressure (Pa) hru_ea
    const float  *u_X;        // wind speed (m/sec)  hru_u
    const float  *Albedo;     // albedo ()
    const float  *Qsisn_Var;  // short wave at snow surface
    const float  *QsiS_Var;  // short wave at snow surface from Slope_Qsi
    const float  *Qlisn_Var;  // long wave at snow surface - through canopy
    const float  *QliVt_Var;  // long wave at snow surface - no canopy

// variable precipitation inputs

    const float  *m_precip_X;	// specific mass of total precip     (kg/m^2) net_p
    const float  *m_snow_X;	// specific mass in snow in precip   (kg/m^2) net_snow
    const float  *m_drift_X;	// specific mass in snow drift       (kg/m^2) Drift
    const float  *m_subl_X;	// specific mass of snow sublimation (kg/m^2) Subl

// put variable precipitation inputs

    float  *m_rain_X;	// specific mass of rain in precip   (kg/m^2) net_rain

// parameters

    const float  *rho_snow_X;       // density of snowfall               (kg/m^3)
    const float  *T_g_X;            // soil temp at depth z_g (C)
    const float  *F_g_X;            // soil flux at depth z_g (C)
    const long   *rain_soil_snow;  //

// Declared variables

    float *snow_store; // accumulates snow till > 1+mm

    void decl(void);

    void init(void);

    void run(void);

    void finish(bool good); // delete local storage used
};

class ClassCRHMCanopyClearing:public ClassModule {

public:

ClassCRHMCanopyClearing(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 2000) {};

float Qsi_, Qli_;

// observation variables

const float *Qsi;
const float *Qli;

// declared observation variables

float *Ts;
float *Qnsn;
float *Qsisn;
float *Qlisn;
float *Qlosn;

// put variables

float *SWE;

// declared variables

float *drip_Cpy;
float *thrufall_Cpy;
float *netRain_Cpy;
float *direct_rain;
float *rain_load;
float *Snow_load;
float *direct_snow;
float *SUnload;
float *Qnsn_Var;
float *Qsisn_Var;
float *Qlisn_Var;

float *net_rain;
float *cum_net_rain;
float *net_snow;
float *cum_net_snow;
float *net_p;
float *intcp_evap;
float *cum_intcp_evap;
float *Subl_Cpy;
float *cum_Subl_Cpy;

float *Cc;
float *k;
float *Tauc;
float *Pa;
float *ra;
float *u_FHt;
float *Pevap;

// variable inputs

const float *hru_t;
const float *hru_u;
const float *hru_rh;
const float *hru_ea;
const float *Albedo;

const float *hru_snow;
const float *hru_rain;
const float *hru_evap;

const float *SolAng;

const float *QsiS_Var;
const float *QsiA_Var;
const float *QliVt_Var;

// declared parameters:

const float *basin_area;   // [BASIN]
const float *hru_area;
const float *hru_elev;
const float *Ht;
const float *LAI;
const float *Sbar;
const float *Z0snow;
const float *Zref;
const float *Zwind;
const float *Zvent;
const float *unload_t;
const float *unload_t_water;

const long *CanopyClearing;
const long *inhibit_evap;


void decl(void);
void init(void);
void run(void);
void finish(bool good);

double delta(float t); // Slope of sat vap p vs t, kPa/�C
double gamma(float Pa, float t); // Psychrometric constant (kPa/�C)
float RHOa(float t, float ea, float Pa); // atmospheric density (kg/m^3)
float lambda(float t); // Latent heat of vaporization (mJ/(kg �C))

ClassCRHMCanopyClearing* klone(string name) const;

};

class ClassSlope_Qsi : public ClassModule {
public:

ClassSlope_Qsi(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
float *QsiS_Var;
float *QsiD_Var;

// declared observations variable
const float *Qsi;

// declared observations
float *QsiS;
float *QsiD;
float *QsiD_Obs;

// variable inputs
const float *Qdro;
const float *Qdfo;
const float *Qdflat;

void decl(void);
void init(void);
void run(void);

ClassSlope_Qsi* klone(string name) const;
};

class ClassfrozenAyers : public ClassModule {
public:

ClassfrozenAyers(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl),
                                    infiltype(NULL) {};
bool SetOpportunityTime;
float SWE_sum;

// declared observation variables
const float *t0_inhibit;   // (mm/day)

// declared variables
float *infil;         // unfrozen infiltration
float *cuminfil;      // cumulative unfrozen infiltration
float *snowinfil;     // frozen infiltration
float *cumsnowinfil;  // cumulative frozen infiltration
float *cummeltrunoff; // cumulative frozen melt runoff
float *runoff;        // cumulative runoff
float *cumrunoff;     // cumulative melt runoff
float *t0_Acc;        // infiltration opportunity time accumulation
float *t0_Var;        // infiltration opportunity time used
float *INF;           //
float *snowmeltD_last; //
long  *Julian_window; // currently in Julian window.
long  *Julian_end;    // Julian window end date.

// variable put
const float *soil_moist;    //
float *meltrunoff;      // [nhru]

// local variables
long *infiltype;
float *SWE_pk;       // last peak SWE

// declared parameters
const float *basin_area;  // [BASIN]
const float *hru_area;
const float *S0;          // surface saturation (mm3/mm3)
const float *Si;          // initial average soil saturation (mm3/mm3)
const float *C;           // coefficient
const float *hru_tsoil;   // soil temperature(�K) of 0-40cm soil layer at start of infiltration
const float *t_ice_lens;   // overnight minimum to cause ice lens after major melt
const float *t0;          // infiltration opportunity time. Set at end of calibration run.
const float *soil_moist_max; // common to smbal to control maximum inflitration.
const long  *t0_Julian;    // Julian date when t0 is primed. '0' value - never reset.
const long  *texture;
const long  *groundcover;

// variable inputs
const float *snowmeltD;   // (mm/day)
const float *SWE;         // (mm)
const float *frostdepth;
const float *net_rain;
const float *hru_tmin;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassfrozenAyers* klone(string name) const;
};

class ClassCRHMCanopyClearingGap:public ClassModule {

public:

ClassCRHMCanopyClearingGap(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

float Qsi_, Qli_;

// observation variables

const float *Qsi;
const float *Qli;

// declared observation variables

float *Ts;
float *Qnsn;
float *Qsisn;
float *Qlisn;
float *Qlosn;

// put variables

float *SWE;

// declared variables

float *drip_Cpy;
float *thrufall_Cpy;
float *netRain_Cpy;
float *direct_rain;
float *rain_load;
float *Snow_load;
float *direct_snow;
float *SUnload;
float *Qnsn_Var;
float *Qsisn_Var;
float *Qlisn_Var;

float *net_rain;
float *cum_net_rain;
float *net_snow;
float *cum_net_snow;
float *net_p;
float *intcp_evap;
float *cum_intcp_evap;
float *Subl_Cpy;
float *cum_Subl_Cpy;

float *Cc;
float *k;
float *Tauc;
float *Pa;
float *ra;
float *u_FHt;
float *Pevap;

// variable inputs

const float *hru_t;
const float *hru_u;
const float *hru_rh;
const float *hru_ea;
const float *Albedo;

const float *hru_snow;
const float *hru_rain;
const float *hru_evap;

const float *SolAng;
const float *cosxs;
const float *cosxsflat;
const float *Qdfo;

const float *QsiS_Var;
const float *QsiA_Var;
const float *QliVt_Var;

// declared parameters:

const float *basin_area;   // [BASIN]
const float *hru_area;
const float *hru_elev;
const float *Ht;
const float *LAI;
const float *Sbar;
const float *Z0snow;
const float *Zref;
const float *Zwind;
const float *Zvent;
const float *unload_t;
const float *unload_t_water;
const float *Surrounding_Ht;
const float *Gap_diameter;

const long *CanopyClearing;
const long *inhibit_evap;


void decl(void);
void init(void);
void run(void);
void finish(bool good);

double delta(float t); // Slope of sat vap p vs t, kPa/�C
double gamma(float Pa, float t); // Psychrometric constant (kPa/�C)
float RHOa(float t, float ea, float Pa); // atmospheric density (kg/m^3)
float lambda(float t); // Latent heat of vaporization (mJ/(kg �C))

ClassCRHMCanopyClearingGap* klone(string name) const;

};

class ClassSoil : public ClassModule {
public:

ClassSoil(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

long snowinfilDiv;
long meltrunoffDiv;
long runoffDiv;
long evapDiv;

// declared observation variables

// declared variables
float *Sd;
float *gw;
float *soil_rechr;
float *soil_moist;
float *soil_gw;
float *gw_flow;
float *soil_ssr;
float *rechr_ssr;
float *soil_runoff;
float *cum_soil_ssr;
float *cum_rechr_ssr;
float *cum_soil_runoff;
float *cum_runoff_to_Sd;
float *soil_gw_D;
float *soil_ssr_D;
float *gw_flow_D;
float *soil_runoff_D;
float *HK_V;
float *HK_A;
float *culvert_Q;
float *culvert_water_H;
float *culvert_water_A;
float *culvert_water_V;
float *culvert_water_O;

// local variables
float *cum_soil_gw;
float *cum_gw_flow;
float *cum_hru_condense;
float *soil_moist_Init;
float *soil_rechr_Init;
float *Sd_Init;
float *gw_Init;
float *SWE_Init;

float *snowinfil_buf;
float *runoff_buf;
float *meltrunoff_buf;
float *hru_evap_buf;

// declared parameters
const float *Sdmax;
const float *Sdinit;
const float *gw_max;
const float *gw_init;
const float *gw_K;
const float *basin_area;   // [BASIN]
const float *hru_area;
const float *soil_rechr_max;
const float *soil_rechr_init;
const float *soil_moist_max;
const float *soil_moist_init;
const float *soil_gw_K;
const float *rechr_ssr_K;
const float *lower_ssr_K;
const float *Sd_ssr_K;
const float *Sd_gw_K;
const long *soil_withdrawal;
const float *channel_slope;
const float *side_slope;
const float *culvert_diam;
const float *culvert_water_Dmax;
const float *number_culverts;

const long *cov_type;
const long *transp_limited;
const long *soil_ssr_runoff;
const long *inhibit_evap;

// variable inputs
const float *infil;
const float *snowinfil;
const float *meltrunoff; // frozen melt runoff
const float *runoff;     // liquid runoff
const float *hru_evap;

// variable put inputs
float *hru_actet;      // [nhru]
float *hru_cum_actet;


// local allocated arrays

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassSoil* klone(string name) const;
};

class Classevap_Resist : public ClassModule {
public:

Classevap_Resist(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

long QsiCnt;
long TsCnt;
long RnObsCnt;
bool BeforeCorrectionRCS;

// declared variables
float *hru_actet;
float *hru_cum_actet;
float *evap;
float *evapD;
float *cum_evap;
float *rc;

// local allocated arrays
float *Pa;

// declared parameters
const float *basin_area;   // [BASIN]
const float *hru_area;
const float *Ht;
const float *Htmax;
const float *Zwind;
const float *hru_elev;
const float *F_Qg;
const float *rcs;
const float *LAImax;
const float *LAImin;
const float *soil_Depth;

const long *evap_type;
const long *inhibit_evap;
const long *soil_type;
const long *s;
const long *PM_method;

// variable inputs
const float *Rn;
const float *RnD;
const float *RnD_POS;
const float *hru_t;
const float *hru_u;
const float *hru_ea;
const float *hru_tmean;
const float *hru_umean;
const float *hru_eamean;
const float *soil_moist;

// declared observations variable
const float *Qsi;
const float *Ts;
const float *RnObs;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classevap_Resist* klone(string name) const;

double gamma(float Pa, float t);         // Psychrometric constant
float lambda(float t);                   // Latent heat of vaporization
double delta(float t);                   // Slope of sat vap p vs t, kPa/�C
float RHOa(float t, float ea, float Pa); // atmospheric density (kg/m^3)
double fdaily(float u, float Ht);        // Drying power f(u) - interval
};

class ClassevapD_Resist : public ClassModule {
public:

ClassevapD_Resist(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

long QsiCnt;
long TsCnt;

// declared variables
float *hru_actet;
float *hru_cum_actet;
float *evapD;
float *cum_evap;
float *rc;

// local allocated arrays
float *Pa;

// declared parameters
const float *basin_area;   // [BASIN]
const float *hru_area;
const float *Ht;
const float *Htmax;
const float *Zwind;
const float *hru_elev;
const float *F_Qg;
const float *rcs;
const float *LAImax;
const float *LAImin;
const float *soil_Depth;

const long *evap_type;
const long *inhibit_evap;
const long *soil_type;
const long *s;
const long *PM_method;

// variable inputs
const float *RnD;
const float *hru_tmean;
const float *hru_umean;
const float *hru_eamean;
const float *soil_moist;

// declared observations variable
const float *Qsi;
const float *Ts;

// declared observation functions
float *Qsi_mean;
float *Tsmean;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassevapD_Resist* klone(string name) const;

double gamma(float Pa, float t);         // Psychrometric constant
float lambda(float t);                   // Latent heat of vaporization
double delta(float t);                   // Slope of sat vap p vs t, kPa/�C
float RHOa(float t, float ea, float Pa); // atmospheric density (kg/m^3)
double fdaily(float u, float Ht);        // Drying power f(u) - interval
};

class ClassShutWall : public ClassModule {
public:

ClassShutWall(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

long Qn_Cnt;
long Qg_Cnt;
float z0;
float d;
float n;


// declared variables
float *hru_actet;
float *hru_cum_actet;
float *evap;
float *evapD;
float *cum_evap;
float *Cc;
float *Cs;
float *Ra;
float *Rc;
float *Rs;
float *ETc;
float *ETs;
float *raa;
float *rca;
float *rcs;
float *rsa;
float *rss;

// declared parameters
const float *basin_area;   // [BASIN]
const float *hru_area;
const float *rs;
const float *hru_elev;
const float *Cr;
const float *LAI;
const float *Ht;
const float *Zwind;
const float *w;
const float *rst;
const float *z0g;
const float *gammab;

const long *inhibit_evap;

// declared observations
const float *hru_u;
const float *hru_t;
const float *hru_ea;
const float *Qn;
const float *Qg;

// variable inputs

// local allocated arrays
float *Pa;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassShutWall* klone(string name) const;

float RHOa(float t, float ea, float Pa); // atmospheric density (kg/m^3)
double gamma(float Pa, float t);         // Psychrometric constant
float lambda(float t);                   // Latent heat of vaporization
double delta(float t);                   // Slope of sat vap p vs t, kPa/�C
};

class ClassShutWallD : public ClassModule {
public:

ClassShutWallD(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

long Qn_Cnt;
long Qg_Cnt;

// declared variables
float *hru_actet;
float *hru_cum_actet;
float *evapD;
float *cum_evap;
float *Cc;
float *Cs;
float *Ra;
float *Rc;
float *Rs;
float *ETc;
float *ETs;
float *raa;
float *rca;
float *rcs;
float *rsa;
float *rss;

// declared parameters
const float *basin_area;   // [BASIN]
const float *hru_area;
const float *rs;
const float *hru_elev;
const float *Cr;
const float *LAI;
const float *Ht;
const float *Zwind;
const float *w;
const float *rst;
const float *z0g;
const float *gammab;

const long *inhibit_evap;

// declared observations
const float *hru_umean;
const float *hru_tmean;
const float *hru_eamean;
const float *Qn;
const float *Qg;

// declared observation functions
float *Qnmean;
float *Qgmean;

// variable inputs

// local allocated arrays
float *Pa;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassShutWallD* klone(string name) const;

float RHOa(float t, float ea, float Pa); // atmospheric density (kg/m^3)
double gamma(float Pa, float t);         // Psychrometric constant
float lambda(float t);                   // Latent heat of vaporization
double delta(float t);                   // Slope of sat vap p vs t, kPa/�C
};

class ClassIceBulb : public ClassModule {
public:

ClassIceBulb(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
float *hru_icebulb;
float *hru_rainI;
float *cumhru_rainI;
float *hru_snowI;
float *cumhru_snowI;
float *cumhru_pI;
float *Pa;

// variable inputs
const float *hru_t;
const float *hru_rh;
const float *hru_p;

// declared parameters
const float *hru_elev;
const float *tmaxI_allrain;
const float *tmaxI_allsnow;

void decl(void);
void init(void);
void run(void);

ClassIceBulb* klone(string name) const;
};

class Classglacier : public ClassModule {
public:

Classglacier(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl){};

// declared observation variables
const float *Qnsn;
const float *QnD;

// declared variables
float *SWE;
float *ICE;
float *z_s;
float *rho;
float *icemeltD;
float *cumicemelt;

float *snowmeltD;
float *cumsnowmelt;
float *LW_ebsm;
float *u_ebsm;
float *Qmelt;
float *Qn_ebsm;
float *Qh_ebsm;
float *Qe_ebsm;
float *Qp_ebsm;
float *Qnsn_Acc;

float *LWmax;
float *net_rainD;

// declared parameters
const float *basin_area;   // [BASIN]
const float *hru_area;
const float *tfactor;
const float *nfactor;
const float *Use_QnD;
const float *ICE_init;
const float *ICE_Albedo;

// variable inputs
const float *tmean;
const float *tmax;
const float *tmin;
const float *umean;
const float *rhmean;
const float *net_rain;
const float *net_snow;
const float *hru_drift;
const float *hru_subl;
const float *Albedo;
const float *sunact;
const float *QdroD;
const float *QdfoD;
const float *sunmax;
const float *Qnsn_Var;

const long  *meltflag;
const long  *delay_melt;

// local allocated arrays

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classglacier* klone(string name) const;
};

class Classlake : public ClassModule {
public:

Classlake(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

  int DaysMonth;
  long ThisMonth;
  bool DoMean;
  bool Ahead;
  long  N_intervals;
  long itime[6];
  
// declared variables
  float *hru_evap;
  float *hru_cum_evap;
  float *hru_actet;
  float *hru_cum_actet;
  float *lake_evap_month;
  float *hru_t_Mmean;
  float *hru_rh_Mmean;
  float *hru_u_Mmean;
  float *hru_t_acc;
  float *hru_rh_acc;
  float *hru_u_acc;
  float *Vw;
  float *Va;
  long  *start_open_day;
  long  *end_open_day;

// get variables:
  const float *hru_t;
  const float *hru_rh;
  const float *hru_u;

// put variables:

// declared parameters
  const float *Meyer_C;
  const float *Meyer_B;
  const float **Meyer_B_def;
  const float *hru_area;
  const float *basin_area;
  const float *hru_lat;
  const float *hru_elev;

  const long *start_open_water;
  const long *end_open_water;

void decl(void);
void init(void);
void run(void);
void add(void);
void process(void);
void finish(bool good);

Classlake* klone(string name) const;
};

class ClassalbedoWinstral : public ClassModule {
public:

ClassalbedoWinstral(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
  float *Albedo;
  float *irdalb;
  float *vdalb;
//  float *balbx;
  float *Ab_t;

// get variables:

// put variables:

  float *net_snow;
  float *SWE;

// declared parameters
  const float *maxdecay;
  const float *power;
  const float *decay_period;
  const float *refresh;
  const float *Albedo_Bare;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassalbedoWinstral* klone(string name) const;
};

#endif
