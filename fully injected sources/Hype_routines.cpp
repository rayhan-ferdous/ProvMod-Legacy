#include <vcl.h>
#pragma hdrstop
#include "Hype_routines.h"
#include "NewModules.h"
#include "DefCRHMGlobal.h"
#include <math.h>
#include <stdlib.h>
#pragma package(smart_init)
using namespace std;
using namespace CRHM;
const float thetalow = 0.1;                     
const float thetaupp = 0.5;                     
const float bulkdensity = 1300;
const float sreroexp = 0.0; 
const float filtPbuf  = 1.0; 
const float filtPother  = 1.0; 
const float filtPinner  = 1.0; 
const float pprelmax  = 1.0; 
const float pprelexp  = 1.0; 
const float Kfr = 1.0; 
const float Nfr = 1.0; 
const float Kadsdes = 1.0; 
const float halfsatTPwater  = 0.05;    
const float maxprodwater    = 0.5;     
const float maxdegradwater  = 0.5;     
const float NPratio         = 1.0/7.2; 
const float NCratio         = 5.7;     
const float maxdenitriwater = 999; 
const float halfsatINwater = 999; 
const float soilerod = 1.0;
const float satact = 1.0;
const float thetapow = 1.0;
const float smfdenitlim = 0.1; 
const float smfdenitpow = 1.0; 
const float halfsatINsoil = 1.0;
const float ldprodpp = 1.0;
const float ldprodsp = 1.0;
const long i_in = 0; 
const long i_on = 1; 
const long i_sp = 2; 
const long i_pp = 3; 
const long i_oc = 4; 
ClassWQ_Hype* ClassWQ_Hype::klone(string name) const
{
freopen("c:\\injection.log", "a", stdout); printf("<ClassWQ_Hype*ClassWQ_Hype::klone(stringname)const @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
{freopen("c:\\injection.log", "a", stdout); printf("</ClassWQ_Hype*ClassWQ_Hype::klone(stringname)const @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);return new ClassWQ_Hype(name);}
freopen("c:\\injection.log", "a", stdout); printf("</ClassWQ_Hype*ClassWQ_Hype::klone(stringname)const @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
}
void ClassWQ_Hype::decl(void)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassWQ_Hype::decl(void) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
    Description = "'Hype module.'";
    declstatvar("partP", NDEFN, "immobile pool of organic phosphorus adsorded to soil particles.", "(kg/km^2)", &partP, &partP_lay, maxsoillayers);
    declstatvar("humusN", NDEFN, "immobile pool of organic nitrogen in soil with slow turnover.", "(kg/km^2)", &humusN, &humusN_lay, maxsoillayers);
    declstatvar("humusP", NDEFN, "immobile pool of organic phosphorus in soil with slow turnover.", "(kg/km^2)", &humusP, &humusP_lay, maxsoillayers);
    declstatvar("humusC", NDEFN, "humusC pool in soil", "(kg/km^2)", &humusC, &humusC_lay, maxsoillayers);
    declstatvar("fastN", NDEFN, "immobile pool of organic nitrogen in soil with rapid turnover.", "(kg/km^2)", &fastN, &fastN_lay, maxsoillayers);
    declstatvar("fastP", NDEFN, "immobile pool of organic phosphorus in soil with rapid turnover.", "(kg/km^2)", &fastP, &fastP_lay, maxsoillayers);
    declstatvar("fastC", NDEFN, "fastC pool in soil", "(kg/km^2)", &fastC, &fastC_lay, maxsoillayers);
    declvar("water", NDEFN, "soil moisture", "(mm)", &water, &water_lay, maxsoillayers);
    declvar("temp", NDEFN, " ", "(�C)", &temp, &temp_lay, maxsoillayers);
    declstatvar("PPrelpool", NDEFN, "pool of delayed PP in runoff", "(kg/km^2)", &PPrelpool, &PPrelpool_lay, maxsoillayers);
    declvar("denitrification", NDEFN, "denitrification (maxsoillayers", "()", &denitrification, &denitrification_lay, maxsoillayers);
    declstatvar("conc_top", NDEFN, "concentration of inorganic nitrogen in soil moisture per land-soil", "(kg/km^2)", &conc_top, &conc_top_lay, numsubstances); 
    declstatvar("conc_bottom", NDEFN, "concentration of organic nitrogen in soil moisture per land-soil", "(kg/km^2)", &conc_bottom, &conc_bottom_lay, numsubstances);
    declstatvar("conc_below", NDEFN, "concentration of soluble (reactive) phosphorus, i.e. phosphate in soil moisture per land-soil", "(kg/km^2)", &conc_below, &conc_below_lay, numsubstances);
    declvar("source", NDEFN, "source of soil water nutrients through mineralization", "()", &source, &source_lay, numsubstances);
    declvar("thickness", NDEFN, "thickness of soil layers", "(mm)", &thickness, &thickness_lay, maxsoillayers); 
    declvar("sink", NDEFN, "sink of nutrients in subroutine)", "(kg/km^2)", &sink, &sink_lay, numsubstances); 
    declvar("sources_plant", NDEFN, "load from plant residues. Indexed as [LAY -> substance]", "(kg/int)", &sources_plant, &sources_plant_lay, numsubstances);
    declvar("sources_fertilizer", NDEFN, "load from fertilizer) Indexed as [LAY -> substance]", "(kg/int)", &sources_fertilizer, &sources_fertilizer_lay, numsubstances);
    declvar("erodedP", NHRU, "eroded phosphorus", "(kg/km^2)", &erodedP);
    declvar("fracminP", NHRU, "part of eroded P in mineral form", "()", &fracminP);
    declvar("csurface", NHRU, "total runoff (concentration surface runoff - surfacerunoff, tilerunoff, soilrunoff layer 1-3)", "(mg/l)", &csurface);
    declvar("totflow", NHRU, "total runoff (surfacerunoff, tilerunoff, soilrunoff layer 1-3))", "((mg/l))", &totflow);
    declvar("nitrification", NHRU, "nitrification", "()", &nitrification);
    declvar("cropuptake", NHRU, "crop uptake of nitrogen", "()", &cropuptake);
    decldiagparam("fc", NDEFN, "[1]", "0", "100", "water content at field capacity", "(mm)", &fc, &fc_lay, maxsoillayers);
    decldiagparam("ep", NDEFN, "[1]", "0", "100", "water content: effectiv porosity", "(mm)", &ep, &ep_lay, maxsoillayers);
    decldiagparam("wp", NDEFN, "[1]", "1", "66", "water content at wilting point", "(mm)", &wp, &wp_lay, maxsoillayers);
    decldiagparam("pw", NDEFN, "[1]", "1", "66", "water content: total porosity", "(mm)", &pw, &pw_lay, maxsoillayers);
    declparam("hru_area", NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);
    declparam("hru_GSL", NHRU, "0.0", "0.0", "90.0", "ground slope - increasing the slope positively, tilts the plane to the north with ASL = 0", "(�)", &hru_GSL);
    declparam("ccmax1", NHRU, "[0]", "0","10", "crop cover during summer", "()", &ccmax1);
    declparam("ccmax2", NHRU, "[0]", "0","10", "crop cover during winter and all year for year round", "()", &ccmax2);
    declparam("gcmax1", NHRU, "[0]", "0","10", "ground cover during summer", "()", &gcmax1);
    declparam("gcmax2", NHRU, "[0]", "0","10", "ground cover during winter and all year for year round", "()", &gcmax2);
    declparam("baredayno1", NHRU, "[1]", "1","366", "spring ploughing", "()", &baredayno1);
    declparam("baredayno2", NHRU, "[1]", "1","366", "sow date/beginning of growing season", "()", &baredayno2);
    declparam("baredayno3", NHRU, "[1]", "1","366", "harvest", "()", &baredayno3);
    declparam("baredayno4", NHRU, "[1]", "1","366", "autumn ploughing", "()", &baredayno4);
    declparam("baredayno5", NHRU, "[1]", "1","366", "winter crops sowing date", "()", &baredayno5);
    decldiagparam("denpar", NHRU, "[1]", "0", "100", "denitrification in soil", "(mm)", &denpar);
    declparam("calcN", NHRU, "[0]", "0", "1", "flag for nitrogen simulation", "()", &calcN);
    declparam("calcP", NHRU, "[0]", "0", "1", "flag for phosphorus simulation", "()", &calcP);
    declparam("calcC", NHRU, "[0]", "0", "1", "flag for carbon simulation", "()", &calcC);
    declparam("conductP", NHRU, "[0]", "0", "1", "flag for conduct P", "()", &conductP);
    declparam("conductN", NHRU, "[0]", "0", "1", "flag for conduct P", "()", &conductN);
    decldiagparam("cohesion", NHRU, "[100]", "0", "1000", "cohesion", "(kPa)", &cohesion);
    decldiagparam("erodibility", NHRU, "[1]", "0", "100", "erodibility", "(g/J)", &erodibility);
    declparam("closewater", NHRU, "[0]", "0", "1", "part[hh] of area (possibly agricultural area) close to water courses", "()", &closewater);
    decldiagparam("buffer", NHRU, "[0]", "0", "1", "part of river length with buffer zones (of river in the area above (e.g. agricultural area))", "()", &buffer);
    declparam("parminfN", NHRU, "[0]", "0", "1", "mineralisation fastN", "()", &parminfN);
    declparam("parminfP", NHRU, "[0]", "0", "1", "mineralisation fastP", "()", &parminfP);
    declparam("pardegrhN", NHRU, "[0]", "0", "1", "degradation humusN", "()", &pardegrhN);
    declparam("pardegrhP", NHRU, "[0]", "0", "1", "degradation humusP", "()", &pardegrhP);
    declparam("pardisfN", NHRU, "[0]", "0", "1", "mineralisation fastN to dissolved ON", "()", &pardisfN);
    declparam("pardisfP", NHRU, "[0]", "0", "1", "mineralisation fastP to dissolved OP", "()", &pardisfP);
    declparam("pardishN", NHRU, "[0]", "0", "1", "mineralisation humusN to dissolved ON", "()", &pardishN);
    declparam("pardishP", NHRU, "[0]", "0", "1", "mineralisation humusP to dissolved OP", "()", &pardishP);
    decldiagparam("klh",    NHRU, "[1]", "0", "100", "speed of transformation from litter to humus", "(1/d)", &klh);
    decldiagparam("klo",    NHRU, "[1]", "0", "100", "speed of transformation from litter to DOC", "(1/d)", &klo);
    decldiagparam("kho",    NHRU, "[1]", "0", "100", "speed of transformation from humus to DOC", "(1/d)", &kho);
    decldiagparam("kof",    NHRU, "[1]", "0", "100", "speed of transformation from DOC to fastC", "(1/d)", &kof);
    decldiagparam("koflim", NHRU, "[1]", "0", "100", "threshold for wetness for transformation DOC to fastC", "()", &koflim);
    decldiagparam("minc",   NHRU, "[1]", "0", "100", "fraction mineralisation to DIC", "()", &minc);
    decldiagparam("soimf",  NHRU, "[1]", "0", "100", "saturation soilmoisture factor", "()", &soimf);
    decldiagparam("soimr",  NHRU, "[1]", "0", "100", "rate soilmoisture factor", "()", &soimr);
    declparam("fertNamount1", NHRU, "[1]", "0", "10000", "fertiliser amount1 N", "(kg/km^2)", &fertNamount1);
    declparam("fertNamount2", NHRU, "[1]", "0", "10000", "fertiliser amount2 N", "(kg/km^2)", &fertNamount2);
    declparam("fertPamount1", NHRU, "[1]", "0", "10000", "fertiliser amount1 P", "(kg/km^2)", &fertPamount1);
    declparam("fertPamount2", NHRU, "[1]", "0", "10000", "fertiliser amount2 P", "(kg/km^2)", &fertPamount2);
    declparam("fertday1", NHRU, "[120]", "0", "366", "day for fertilizing 1 (dayno)", "()", &fertday1);
    declparam("fertday2", NHRU, "[0]", "0", "366", "day for fertilizing 2 (dayno)", "()", &fertday2);
    declparam("resdayno", NHRU, "[1]", "0", "366", "day for residual (dayno), code 0 give residuals every day)", "()", &resdayno);
    declparam("manday1", NHRU, "[0]", "0", "366", "day for manureing 1)", "()", &manday1);
    declparam("manday2", NHRU, "[0]", "0", "366", "day for manureing 2)", "()", &manday2);
    declparam("fertdown1", NHRU, "[0.0]", "0", "1", "part[hh] of fertilizer amount1 ploughed down", "()", &fertdown1);
    declparam("fertdown2", NHRU, "[0.0]", "0", "1", "part[hh] of fertilizer amount2 ploughed down", "()", &fertdown2);
    declparam("mandown1", NHRU, "[0.0]", "0", "1", "part[hh] of manure amount1 ploughed down", "()", &mandown1);
    declparam("mandown2", NHRU, "[0.0]", "0", "1", "part[hh] of manure amount2 ploughed down", "()", &mandown2);
    declparam("manNamount1", NHRU, "[0.0]", "0", "10000", "manure amount1 N", "(kg/km^2)", &manNamount1);
    declparam("manNamount2", NHRU, "[0.0]", "0", "10000", "manure amount2 N", "(kg/km^2)", &manNamount2);
    declparam("manPamount1", NHRU, "[0.0]", "0", "10000", "manure amount1 P", "(kg/km^2)", &manPamount1);
    declparam("manPamount2", NHRU, "[0.0]", "0", "10000", "manure amount2 P", "(kg/km^2)", &manPamount2);
    declparam("resNamount", NHRU, "[0.0]", "0", "10000", "residual amount of N", "(kg/km^2)", &resNamount);
    declparam("resPamount", NHRU, "[0.0]", "0", "10000", "residual amount of P", "(kg/km^2)", &resPamount);
    declparam("resCamount", NHRU, "[0.0]", "0", "1", "litter fall of C", "(kg/km^2)", &resCamount);
    declparam("resfast", NHRU, "[0.0]", "0", "1", "part[hh] of residual amount to fastN/P pool (rest to humusN/P)", "()", &resfast);
    declparam("resdown", NHRU, "[0.0]", "0", "1", "part[hh] of residual amount to fastN/P pool (rest to humusN/P)", "()", &resdown);
    declparam("fertperiod", NHRU, "[1]", "1", "100", "days for fertilization.)", "()", &fertperiod);
    declparam("litterperiod", NHRU, "[1]", "1", "100", "days for litterfall.)", "()", &litterperiod);
    decldiagparam("part", NHRU, "[1.0]", "0", "1", "fraction of HRU area under current crop.", "()", &part);
    decldiagparam("inorgpart", NHRU, "[0.5]", "0", "1", "fraction of HRU for manure IN-ON.", "()", &inorgpart);
    decldiagparam("fastpart", NHRU, "[0.5]", "0", "1", "fraction of HRU for manure fastP-humusP.", "()", &fastpart);
    declparam("humusN_init", NDEFN, "[0.0]", "0", "1000", "immobile pool of organic nitrogen in soil with slow turnover.", "(kg/km^2)", &humusN_init, &humusN_init_lay, maxsoillayers);
    declparam("humusP_init", NDEFN, "[0.0]", "0", "1000", "immobile pool of organic phosphorus in soil with slow turnover.", "(kg/km^2)", &humusP_init, &humusP_init_lay, maxsoillayers);
    declparam("humusC_init", NDEFN, "[0.0]", "0", "1000", "humusC pool in soil", "(kg/km^2)", &humusC_init, &humusC_init_lay, maxsoillayers);
    declparam("fastN_init", NDEFN, "[0.0]", "0", "1000", "immobile pool of organic nitrogen in soil with rapid turnover.", "(kg/km^2)", &fastN_init, &fastN_init_lay, maxsoillayers);
    declparam("fastP_init", NDEFN, "[0.0]", "0", "1000", "immobile pool of organic phosphorus in soil with rapid turnover.", "(kg/km^2)", &fastP_init, &fastP_init_lay, maxsoillayers);
    declparam("fastC_init", NDEFN, "[0.0]", "0", "1000", "fastC pool in soil", "(kg/km^2)", &fastC_init, &fastC_init_lay, maxsoillayers);
    declparam("N_uptake", NDEFN, "[1]", "0", "10", "plant N uptake per day.", "(kg/km^2)", &N_uptake, &N_uptake_lay, maxsoillayers2);
    declparam("P_uptake", NDEFN, "[1]", "0", "10", "plant P uptake per day.", "(kg/km^2)", &P_uptake, &P_uptake_lay, maxsoillayers2);
    declgetvar("*", "hru_t", "(�C)", &hru_t);
    declgetvar("*", "SWE", "(mm)", &SWE);
    declgetvar("*", "net_rain", "(mm)", &net_rain);
    declgetvar("*", "runoff", "(mm)", &runoff);
    declgetvar("*", "soil_moist", "(mm)", &soil_moist);
    declgetvar("*", "soil_rechr", "(mm)", &soil_rechr);
    declgetvar("*", "soil_rechr_to_Hype_D_mWQ", "(mg)", &soil_rechr_to_Hype_D_mWQ);
    declgetvar("*", "soil_lower_to_Hype_D_mWQ", "(mg)", &soil_lower_to_Hype_D_mWQ);
    declgetparam("*", "soil_moist_max", "(mm)", &soil_moist_max);
    declgetparam("*", "soil_rechr_max", "(mm)", &soil_rechr_max);
freopen("c:\\injection.log", "a", stdout); printf("</voidClassWQ_Hype::decl(void) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
}
void ClassWQ_Hype::init(void)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassWQ_Hype::init(void) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
    nhru = getdim(NHRU);
    nlay = getdim(NLAY);
    for(hh = 0; hh < nhru; ++hh)
    {
        thickness_lay[0][hh] = soil_rechr_max[hh]/ep[hh];
        thickness_lay[1][hh] = (soil_moist_max[hh] - soil_rechr_max[hh])/ep[hh];
        thickness_lay[2][hh] = soil_moist_max[hh]/ep[hh];
        /*
            if(calcN[hh] && !(i_in[hh] && i_on[hh])){
              String SS = string("'" + Name + " (WQ_Hype)'  parameter calcN set and i_in and/or i_on not assigned in HRU ").c_str() + IntToStr(hh+1);
              CRHMException TExcept(SS.c_str(), TERMINATE);
              LogError(TExcept);
            }
            if(calcP[hh] && !(i_sp[hh] && i_pp[hh])){
              String SS = string("'" + Name + " (WQ_Hype)'  parameter calcP set and i_sp and/or i_pp not assigned in HRU ").c_str() + IntToStr(hh+1);
              CRHMException TExcept(SS.c_str(), TERMINATE);
              LogError(TExcept);
            }
            if(calcC[hh] && !i_oc){
              String SS = string("'" + Name + " (WQ_Hype)'  parameter calcC set and i_oc not assigned in HRU ").c_str() + IntToStr(hh+1);
              CRHMException TExcept(SS.c_str(), TERMINATE);
              LogError(TExcept);
            }
        */
        for(long ll = 0; ll < maxsoillayers; ++ll)
        {
            humusN_lay[ll][hh] = humusN_init_lay[ll][hh];
            humusP_lay[ll][hh] = humusP_init_lay[ll][hh];
            humusC_lay[ll][hh] = humusC_init_lay[ll][hh];
            fastN_lay[ll][hh] = fastN_init_lay[ll][hh];
            fastP_lay[ll][hh] = fastP_init_lay[ll][hh];
            fastC_lay[ll][hh] = fastC_init_lay[ll][hh];
            partP_lay[ll][hh];
            PPrelpool_lay[ll][hh];
            denitrification_lay[ll][hh];
        }
        for(long ll = 0; ll < numsubstances; ++ll)
        {
            conc_top_lay[ll][hh] = 0.0;
            conc_bottom_lay[ll][hh] = 0.0;
            conc_below_lay[ll][hh] = 0.0;
            source_lay[ll][hh] = 0.0;
            sink_lay[ll][hh] = 0.0;
            sources_fertilizer_lay[ll][hh] = 0.0;
            sources_plant_lay[ll][hh] = 0.0;
            cropuptake[hh] = 0.0;
        }
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidClassWQ_Hype::init(void) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
}
void ClassWQ_Hype::run(void)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassWQ_Hype::run(void) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
    nstep = getstep()% Global::Freq;
    if(nstep == 1 || Global::Freq == 1)  
    {
        dayno = julian("now");
        for(hh = 0; chkStruct(); ++hh)
        {
            water_lay[0][hh] = soil_rechr[hh];
            water_lay[1][hh] = soil_moist[hh] - soil_rechr[hh];
            /*
                soil_carbon_pool_transformations(calcC[hh], wp_lay, fc_lay, pw_lay, thickness_lay,
                klh[hh], klo[hh], kho[hh], kof[hh], koflim[hh], minc[hh], soimf[hh], soimr[hh]);
                runoff_pp_by_erosion(net_rain[hh], totflow[hh], totflow[hh], csurface[hh], csoil_top_lay, csoil_bottom_lay,);
            */
            soil_np_processes(calcN[hh], calcP[hh], calcC[hh], hru_area[hh], fc_lay, ep_lay,
                              N_uptake_lay, P_uptake_lay, thickness_lay, fertperiod[hh], litterperiod[hh],
                              source_lay, nitrification,
                              denitrification_lay, cropuptake, sources_fertilizer_lay, sources_plant_lay,
                              pardisfN[hh], pardisfP[hh], pardishN[hh], pardishP[hh], parminfN[hh],
                              parminfP[hh], pardegrhN[hh], denpar[hh], pardegrhP[hh]);
        } 
    } 
freopen("c:\\injection.log", "a", stdout); printf("</voidClassWQ_Hype::run(void) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
}
void ClassWQ_Hype::finish(bool good)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassWQ_Hype::finish(boolgood) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
    for(hh = 0; chkStruct(); ++hh)
    {
        LogMessage(hh, string("'" + Name + " (WQ_Hype)'").c_str(), BLANK);
    }
    LogDebug(" ");
freopen("c:\\injection.log", "a", stdout); printf("</voidClassWQ_Hype::finish(boolgood) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
}
void ClassWQ_Hype::soil_np_processes(const long calcN, const long calcP, const float calcC, const float area, const float **fc_lay, const float **ep_lay, const float **N_uptake_lay, const float **P_uptake_lay, float **thickness_lay, const long fertperiod, const long litterperiod, float **source_lay, float *nitrification, float **denitrification_lay, float *cropuptake, float **sources_fertilizer_lay, float **sources_plant_lay, const float pardisfN, const float pardisfP, const float pardishN, const float pardishP, const float parminfN, const float parminfP, const float pardegrhN, const float denpar, const float pardegrhP)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassWQ_Hype::soil_np_processes(constlongcalcN,constlongcalcP,constfloatcalcC,constfloatarea,constfloat**fc_lay,constfloat**ep_lay,constfloat**N_uptake_lay,constfloat**P_uptake_lay,float**thickness_lay,constlongfertperiod,constlonglitterperiod,float**source_lay,float*nitrification,float**denitrification_lay,float*cropuptake,float**sources_fertilizer_lay,float**sources_plant_lay,constfloatpardisfN,constfloatpardisfP,constfloatpardishN,constfloatpardishP,constfloatparminfN,constfloatparminfP,constfloatpardegrhN,constfloatdenpar,constfloatpardegrhP) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
    /*    USE MODVAR, ONLY : numsubstances,     & 10,     & i_in
    long, INTENT(IN) :: i                           
    long, INTENT(IN) :: j                           
    LOGICAL, INTENT(IN) :: calcN                    
    LOGICAL, INTENT(IN) :: calcP                    
    LOGICAL, INTENT(IN) :: calcC                    
    long, INTENT(IN) :: dayno                       
    float, INTENT(IN)    :: area                     
    float, INTENT(IN)    :: wp(10)        
    float, INTENT(IN)    :: fc(10)        
    float, INTENT(IN)    :: ep(10)        
    float, INTENT(IN)    :: common_uptake(2,2)       
    float, INTENT(IN)    :: thickness[maxsoillayers] 
    float, INTENT(IN)    :: ndays                    
    float, INTENT(IN)    :: ldays                    
    float, INTENT(OUT)   :: source(numsubstances)    
    float, INTENT(OUT)   :: sink(numsubstances)      
    float, INTENT(OUT)   :: nitrification            
    float, INTENT(OUT)   :: denitrification(maxsoillayers)  
    float, INTENT(OUT)   :: cropuptake               
    float, INTENT(OUT)   :: sources(2,numsubstances)    
    float, INTENT(IN)    :: pardisfN            
    float, INTENT(IN)    :: pardisfP            
    float, INTENT(IN)    :: pardishN            
    float, INTENT(IN)    :: pardishP            
    float, INTENT(IN)    :: parminfN            
    float, INTENT(IN)    :: parminfP            
    float, INTENT(IN)    :: pardegrhN           
    float, INTENT(IN)    :: denpar              
    float, INTENT(IN)    :: pardegrhP           
    TYPE(soilstatetype),INTENT(INOUT)  :: soilstate 
    */
    crop_sources(calcN, calcP, calcC, fertperiod, litterperiod, area, thickness_lay, sources_fertilizer_lay, sources_plant_lay); 
    soil_pool_transformations(calcN, calcP, wp_lay, fc_lay, ep_lay, thickness_lay, source_lay,
                              pardisfN, pardisfP, pardishN, pardishP, parminfN, parminfP, pardegrhN, pardegrhP);   
    nitrification[hh] = source_lay[i_in][hh];
    plant_uptake(calcN, calcP, N_uptake_lay, P_uptake_lay, wp_lay, thickness_lay, water_lay, conc_top_lay, conc_bottom_lay, sink_lay);
    if(i_in >= 0)
        cropuptake[hh] = sink_lay[i_in][hh];
    if(calcN)
    {
        denitrification_lay[0][hh] = 0.0;
        denitrification_lay[1][hh] = 0.0;
        denitrification_lay[2][hh] = 0.0;
        if(thickness_lay[0][hh] > 0.0)
            soil_denitrification(wp_lay[0][hh] + fc_lay[0][hh] + ep_lay[0][hh], denpar, soil_moist, hru_t[hh], conc_top_lay, sink_lay);
        denitrification_lay[0][hh] = sink_lay[i_in][hh];
        if(thickness_lay[1][hh] > 0.0)
            soil_denitrification(wp_lay[1][hh] + fc_lay[1][hh] + ep_lay[1][hh], denpar, soil_moist, hru_t[hh], conc_bottom_lay, sink_lay);
        denitrification_lay[1][hh] = sink_lay[i_in][hh];
        if(thickness_lay[2][hh] > 0.0)
            soil_denitrification(wp_lay[2][hh] + fc_lay[2][hh] + ep_lay[2][hh], denpar, soil_moist, hru_t[hh], conc_below_lay, sink_lay);
        denitrification_lay[2][hh] = sink_lay[i_in][hh];
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidClassWQ_Hype::soil_np_processes(constlongcalcN,constlongcalcP,constfloatcalcC,constfloatarea,constfloat**fc_lay,constfloat**ep_lay,constfloat**N_uptake_lay,constfloat**P_uptake_lay,float**thickness_lay,constlongfertperiod,constlonglitterperiod,float**source_lay,float*nitrification,float**denitrification_lay,float*cropuptake,float**sources_fertilizer_lay,float**sources_plant_lay,constfloatpardisfN,constfloatpardisfP,constfloatpardishN,constfloatpardishP,constfloatparminfN,constfloatparminfP,constfloatpardegrhN,constfloatdenpar,constfloatpardegrhP) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
}
void  ClassWQ_Hype::crop_sources(const long calcN, const long calcP, const float calcC, const long fertperiod, const long litterperiod, const float area, float **thickness, float **sources_fertilizer_lay, float **sources_plant_lay)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassWQ_Hype::crop_sources(constlongcalcN,constlongcalcP,constfloatcalcC,constlongfertperiod,constlonglitterperiod,constfloatarea,float**thickness,float**sources_fertilizer_lay,float**sources_plant_lay) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
    /*
        USE MODVAR, ONLY : numsubstances, 10, cropdata, i_in,i_on,i_sp,i_pp,i_oc, prevdoy
        Argument declarations
        INTEGER, INTENT(IN) :: i                        !<subbasin
        INTEGER, INTENT(IN) :: j                        !<class
        INTEGER, INTENT(IN) :: dayno                    !<day number of the year
        LOGICAL, INTENT(IN) :: calcN                    !<Status of nitrogen simulation
        LOGICAL, INTENT(IN) :: calcP                    !<Status of phosphorus simulation
        LOGICAL, INTENT(IN) :: calcC                    !<Status of organic carbon simulation
        float, INTENT(IN)    :: ndays                    !<number of days to spread fertilizer
        float, INTENT(IN)    :: ldays                    !<number of days to spread plant residuals
        float, INTENT(IN)    :: area                   !<class area (km2)
        float, INTENT(IN)    :: thickness(maxsoillayers) !<thickness of soil layers (m)
        TYPE(soilstatetype),INTENT(INOUT)  :: soilstate !<Soil states
        float, INTENT(OUT)   :: sources(2,numsubstances) !<load from fertilizer and plant residues (kg/timestep) ****now sources_i_in_lay etc.***
    */
    long k,kcrop;
    float common_nadd[maxsoillayers][numsubstances]; 
    float common_padd[maxsoillayers][numsubstances]; 
    float common_nres[maxsoillayers][numsubstances]; 
    float common_pres[maxsoillayers][numsubstances]; 
    float common_cres[maxsoillayers][numsubstances]; 
    float littdays;
    for(long ll = 0; ll < numsubstances; ++ll)
    {
        sources_fertilizer_lay[ll][hh] = 0.0;
        sources_plant_lay[ll][hh] = 0.0;
    }
    if(!(calcN || calcP || calcC))
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassWQ_Hype::crop_sources(constlongcalcN,constlongcalcP,constfloatcalcC,constlongfertperiod,constlonglitterperiod,constfloatarea,float**thickness,float**sources_fertilizer_lay,float**sources_plant_lay) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);return;}
    for (long ii = 0.0; ii < maxsoillayers; ++ii)
    {
        for (long kk = 0.0; kk < numsubstances; ++kk)
        {
            common_nadd[ii][kk]   = 0.0;
            common_padd[ii][kk]   = 0.0;
            common_nres[ii][kk]   = 0.0;
            common_pres[ii][kk]   = 0.0;
            common_cres[ii][kk]   = 0.0;
        }
    } 
    Word Y,M,D;
    Global::DTnow.DecodeDate(&Y,&M,&D);
    long prevdoy = (int)(EncodeDate((Word)Y-1, (Word)12, (Word)31) - EncodeDate((Word)Y-1, (Word)1, (Word)1)) + 1; 
    if((dayno >= fertday1[hh] && dayno < fertday1[hh] + fertperiod)  ||
            (dayno < fertday1[hh] + fertperiod - prevdoy))
    {
        if(thickness[1][hh] > 0.0)
        {
            common_nadd[0][0] = common_nadd[0][0] + part[hh] * fertNamount1[hh] * (1.0 - fertdown1[hh]) / fertperiod;
            common_padd[0][0] = common_padd[0][0] + part[hh] * fertPamount1[hh] * (1.0 - fertdown1[hh]) / fertperiod;
            common_nadd[1][0] = common_nadd[1][0] + part[hh] * fertNamount1[hh] * fertdown1[hh] / fertperiod; 
            common_padd[1][0] = common_padd[1][0] + part[hh] * fertPamount1[hh] * fertdown1[hh] / fertperiod;
        }
        else
        {
            common_nadd[0][0] = common_nadd[0][0] + part[hh] * fertNamount1[hh] / fertperiod;
            common_padd[0][0] = common_padd[0][0] + part[hh] * fertPamount1[hh] / fertperiod;
        }
    } 
    if((dayno >= fertday2[hh] && dayno < fertday2[hh] + fertperiod)  ||
            (dayno < fertday2[hh] + fertperiod - prevdoy))
    {
        if(thickness[1][hh] > 0.0)
        {
            common_nadd[0][0] = common_nadd[0][0] + part[hh] * fertNamount2[hh] * (1.0 - fertdown2[hh]) / fertperiod;
            common_padd[0][0] = common_padd[0][0] + part[hh] * fertPamount2[hh] * (1.0 - fertdown2[hh]) / fertperiod;
            common_nadd[1][0] = common_nadd[1][0] + part[hh] * fertNamount2[hh] * fertdown2[hh] / fertperiod; 
            common_padd[1][0] = common_padd[1][0] + part[hh] * fertPamount2[hh] * fertdown2[hh] / fertperiod;
        }
        else
        {
            common_nadd[0][0] = common_nadd[0][0] + part[hh] * fertNamount2[hh] / fertperiod;
            common_padd[0][0] = common_padd[0][0] + part[hh] * fertPamount2[hh] / fertperiod;
        }
    } 
    if((dayno >= manday1[hh] && dayno < manday1[hh] + fertperiod)  ||
            (dayno < manday1[hh] + fertperiod - prevdoy))
    {
        if(thickness[2][hh] > 0.0)
        {
            common_nadd[0][0] = common_nadd[0][0] + part[hh] * manNamount1[hh] * (1.0 - mandown1[hh]) * inorgpart[hh] / fertperiod;
            common_padd[0][0] = common_padd[0][0] + part[hh] * manPamount1[hh] * (1.0 - mandown1[hh]) * fastpart[hh] / fertperiod;
            common_nadd[0][1] = common_nadd[0][1] + part[hh] * manNamount1[hh] * (1.0 - mandown1[hh]) * (1.-inorgpart[hh]) / fertperiod;
            common_padd[0][1] = common_padd[0][1] + part[hh] * manPamount1[hh] * (1.0 - mandown1[hh]) * (1.-fastpart[hh]) / fertperiod;
            common_nadd[1][0] = common_nadd[1][0] + part[hh] * manNamount1[hh] * mandown1[hh] * inorgpart[hh] / fertperiod;
            common_padd[1][0] = common_padd[1][0] + part[hh] * manPamount1[hh] * mandown1[hh] * fastpart[hh] / fertperiod;
            common_nadd[1][1] = common_nadd[1][1] + part[hh] * manNamount1[hh] * mandown1[hh] * (1.0-inorgpart[hh]) / fertperiod;
            common_padd[1][1] = common_padd[1][1] + part[hh] * manPamount1[hh] * mandown1[hh] * (1.0-fastpart[hh]) / fertperiod;
        }
        else
        {
            common_nadd[0][0] = common_nadd[0][0] + part[hh] * manNamount1[hh] * inorgpart[hh] / fertperiod;
            common_padd[0][0] = common_padd[0][0] + part[hh] * manPamount1[hh] * fastpart[hh] / fertperiod;
            common_nadd[0][1] = common_nadd[0][1] + part[hh] * manNamount1[hh] * (1.0 - inorgpart[hh]) / fertperiod;
            common_padd[0][1] = common_padd[0][1] + part[hh] * manPamount1[hh] * (1.0 - fastpart[hh]) / fertperiod;
        }
    } 
    if((dayno >= manday2[hh] && dayno < manday2[hh] + fertperiod)  || (dayno < manday2[hh] + fertperiod - prevdoy))
    {
        if(thickness[1][hh] > 0.0)
        {
            common_nadd[0][0] = common_nadd[0][0] + part[hh] * manNamount2[hh] * (1.0 - mandown2[hh]) * inorgpart[hh] / fertperiod;
            common_padd[0][0] = common_padd[0][0] + part[hh] * manPamount2[hh] * (1.0 - mandown2[hh]) * fastpart[hh] / fertperiod;
            common_nadd[0][1] = common_nadd[0][1] + part[hh] * manNamount2[hh] * (1.0 - mandown2[hh]) * (1.-inorgpart[hh]) / fertperiod;
            common_padd[0][1] = common_padd[0][1] + part[hh] * manPamount2[hh] * (1.0 - mandown2[hh]) * (1.-fastpart[hh]) / fertperiod;
            common_nadd[1][0] = common_nadd[1][0] + part[hh] * manNamount2[hh] * mandown2[hh] * inorgpart[hh] / fertperiod;
            common_padd[1][0] = common_padd[1][0] + part[hh] * manPamount2[hh] * mandown2[hh] * fastpart[hh] / fertperiod;
            common_nadd[1][1] = common_nadd[1][1] + part[hh] * manNamount2[hh] * mandown2[hh] * (1.0-inorgpart[hh]) / fertperiod;
            common_padd[1][1] = common_padd[1][1] + part[hh] * manPamount2[hh] * mandown2[hh] * (1.0-fastpart[hh]) / fertperiod;
        }
        else
        {
            common_nadd[0][0] = common_nadd[0][0] + part[hh] * manNamount2[hh] * inorgpart[hh] / fertperiod;
            common_padd[0][0] = common_padd[0][0] + part[hh] * manPamount2[hh] * fastpart[hh] / fertperiod;
            common_nadd[0][1] = common_nadd[0][1] + part[hh] * manNamount2[hh] * (1.0 - inorgpart[hh]) / fertperiod;
            common_padd[0][1] = common_padd[0][1] + part[hh] * manPamount2[hh] * (1.0 - fastpart[hh]) / fertperiod;
        }
    } 
    if(resdayno[hh] == 0) 
        littdays = 365.0;   
    else
        littdays = litterperiod; 
    if(resdayno[hh] == 0  ||
            ((dayno >= resdayno[hh] && dayno < resdayno[hh] + littdays)  ||
             (dayno < resdayno[hh] + littdays - prevdoy)))
    {
        if(thickness[1][hh] > 0.0)
        {
            common_nres[0][0] = common_nres[0][0] + resfast[hh] * part[hh] * resNamount[hh] * (1.0 - resdown[hh]) / littdays;
            common_nres[0][1] = common_nres[0][1] + (1.0 - resfast[hh]) * part[hh] * resNamount[hh] * (1.0 - resdown[hh]) / littdays;
            common_pres[0][0] = common_pres[0][0] + resfast[hh] * part[hh] * resPamount[hh] * (1.0 - resdown[hh]) / littdays;
            common_pres[0][1] = common_pres[0][1] + (1.0 - resfast[hh]) * part[hh] * resPamount[hh] * (1.0 - resdown[hh]) / littdays;
            common_nres[1][0] = common_nres[1][0] + resfast[hh] * part[hh] * resNamount[hh] * resdown[hh] / littdays;
            common_nres[1][1] = common_nres[1][1] + (1.0 - resfast[hh]) * part[hh] * resNamount[hh] * resdown[hh] / littdays;
            common_pres[1][0] = common_pres[1][0] + resfast[hh] * part[hh] * resPamount[hh] * resdown[hh] / littdays;
            common_pres[1][1] = common_pres[1][1] + (1.0 - resfast[hh]) * part[hh] * resPamount[hh] * resdown[hh] / littdays;
            common_cres[0][0] = common_cres[0][0] + part[hh] * resCamount[hh] * (1.0 - resdown[hh]) / littdays;  
            common_cres[1][0] = common_cres[1][0] + part[hh] * resCamount[hh] * resdown[hh] / littdays;
        }
        else
        {
            common_nres[0][0] = common_nres[0][0] + resfast[hh] * part[hh] * resNamount[hh] / littdays;
            common_nres[0][1] = common_nres[0][1] + (1.0 - resfast[hh]) * part[hh] * resNamount[hh] / littdays;
            common_pres[0][0] = common_pres[0][0] + resfast[hh] * part[hh] * resPamount[hh] / littdays;
            common_pres[0][1] = common_pres[0][1] + (1.0 - resfast[hh]) * part[hh] * resPamount[hh] / littdays;
            common_cres[0][0] = common_cres[0][0] + part[hh] * resCamount[hh] / littdays;
        }
    }
    if(calcN)
    {
        common_nadd[0][0] += soil_rechr_to_Hype_D_mWQ[hh]; 
        common_nadd[1][0] += soil_lower_to_Hype_D_mWQ[hh]; 
    }
    if(calcP)
    {
        common_padd[0][0] += soil_rechr_to_Hype_D_mWQ[hh]; 
        common_padd[1][0] += soil_lower_to_Hype_D_mWQ[hh]; 
    }
    if(calcN  &&  SUM(common_nadd, 1) > 0.0)
    {
        if(water_lay[0][hh] > 0.0)
        {
            add_source_to_water(water_lay[0][hh], 1, &conc_top_lay[i_in][hh], common_nadd[0][0]); 
            sources_fertilizer_lay[i_in][hh] += common_nadd[0][0]*area; 
        }
        else  
        {
            production_pool(1, fastN_lay, common_nadd, 0);
            sources_fertilizer_lay[i_on][hh] += common_nadd[0][0]*area; 
        }
        if(water_lay[1][hh] > 0.0)
        {
            add_source_to_water(water_lay[1][hh], 1, &conc_bottom_lay[i_in][hh], common_nadd[1][0]);
            sources_fertilizer_lay[i_in][hh] += common_nadd[1][0]*area; 
        }
        else if(thickness[1][hh] > 0.0)
        {
            production_pool(1, fastN_lay, common_nadd, 1);
            sources_fertilizer_lay[i_on][hh] += common_nadd[1][0]*area; 
        }
    }
    if(calcP  &&  SUM(common_padd, 1) > 0.0)
    {
        if(water_lay[0][hh] > 0.0)
        {
            add_source_to_water(water_lay[0][hh], 1, &conc_top_lay[i_sp][hh], common_padd[0][0]);
            sources_fertilizer_lay[i_sp][hh] += common_padd[0][0]*area;        
        }
        else
        {
            production_pool(1, fastP_lay, common_padd, 0);
            sources_fertilizer_lay[i_pp][hh] += common_padd[0][0]*area; 
        }
        if(water_lay[1][hh] > 0.0)
        {
            add_source_to_water(water_lay[1][hh], 1, &conc_bottom_lay[i_sp][hh], common_padd[1][0]);
            sources_fertilizer_lay[i_sp][hh] += common_padd[1][1]*area; 
        }
        else if(thickness[1][hh] > 0.0)
        {
            production_pool(1, fastP_lay, common_padd, 1);
            sources_fertilizer_lay[i_pp][hh] += common_padd[2][1]*area; 
        }
    }
    if(calcN && SUM(common_nadd, 1) > 0.0)
    {
        if(thickness[1][hh] > 0.0)
        {
            production_pool(maxsoillayers, fastN_lay, common_nadd, 1); 
            sources_fertilizer_lay[i_on][hh] += SUM(common_nadd, 1)*area;  
        }
        else
        {
            production_pool(1, fastN_lay, common_nadd, 1);
            sources_fertilizer_lay[i_on][hh] += common_nadd[1][2]*area;       
        }
    }
    if(calcP  &&  SUM(common_padd, 1) > 0.0)
    {
        if(thickness[1][hh] > 0.0)
        {
            production_pool(maxsoillayers, fastP_lay, common_padd, 1); 
            sources_fertilizer_lay[i_pp][hh] += SUM(common_padd, 1)*area; 
        }
        else  
        {
            production_pool(1, fastP_lay, common_padd, 1);
            sources_fertilizer_lay[i_pp][hh] += common_padd[1][2]*area; 
        }
    }
    if(calcN  &&  (SUM(common_nres, 1) + SUM(common_nres, 1)) > 0.0)
    {
        if(thickness[1][hh] > 0.0)
        {
            production_pool(maxsoillayers, fastN_lay, common_nres, 0); 
            production_pool(maxsoillayers, humusN_lay, common_nres, 1);
        }
        else  
        {
            production_pool(1, fastN_lay, common_nres, 0);
            production_pool(1, humusN_lay, common_nres,1);
        }
        sources_plant_lay[i_on][hh] = (SUM(common_nres, 0) + SUM(common_nres, 1))*area; 
    }
    if(calcP && (SUM(common_pres, 0) + SUM(common_pres, 1)) > 0.0)
    {
        if(thickness[1][hh]  > 0.0)
        {
            production_pool(maxsoillayers, fastP_lay, common_pres, 0);
            production_pool(maxsoillayers, humusP_lay, common_pres, 1);
        }
        else  
        {
            production_pool(1, fastP_lay, common_pres, 0);
            production_pool(1, humusP_lay, common_pres, 1);
        }
        sources_plant_lay[i_pp][hh] = (SUM(common_pres, 0) + SUM(common_pres, 1))*area; 
    }
    if(calcC  &&  (SUM(common_cres, 0) + SUM(common_cres, 1)) > 0.0)
    {
        if(thickness[1][hh] > 0.0)
            production_pool(maxsoillayers, fastC_lay, common_cres, 0); 
        else 
            production_pool(1, fastC_lay, common_cres, 0); 
        if(i_oc)
            sources_plant_lay[i_oc][hh] = (SUM(common_cres, 0) + SUM(common_cres, 1))*area; 
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidClassWQ_Hype::crop_sources(constlongcalcN,constlongcalcP,constfloatcalcC,constlongfertperiod,constlonglitterperiod,constfloatarea,float**thickness,float**sources_fertilizer_lay,float**sources_plant_lay) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
}
void ClassWQ_Hype::soil_pool_transformations(const long calcN, long long calcP, const float **wp, const float **fc, const float **ep, float **thickness_lay, float **source_lay, const float pardisfN, const float pardisfP, const float pardishN, const float pardishP, const float minfNpar, const float minfPpar, const float degrhNpar, const float degrhPpar)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassWQ_Hype::soil_pool_transformations(constlongcalcN,longlongcalcP,constfloat**wp,constfloat**fc,constfloat**ep,float**thickness_lay,float**source_lay,constfloatpardisfN,constfloatpardisfP,constfloatpardishN,constfloatpardishP,constfloatminfNpar,constfloatminfPpar,constfloatdegrhNpar,constfloatdegrhPpar) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
    /*
        USE MODVAR, ONLY : numsubstances, maxsoillayers, i_in,i_on,i_sp,i_pp
        USE HYPEVARIABLES, ONLY : satact, Thetapow, Thetalow,T hetaupp
    Argument declarations
        long, INTENT(IN) :: i                        !<current subbasin
        long, INTENT(IN) :: j                        !<current slc-class
        LOGICAL, INTENT(IN) :: calcN    !<flag for nitrogen simulation
        LOGICAL, INTENT(IN) :: calcP    !<flag for phosphorus simulation
        float, INTENT(IN)    :: wp(maxsoillayers)        !<water content at wilting point (mm)
        float, INTENT(IN)    :: fc(maxsoillayers)        !<water content at field capacity (mm)
        float, INTENT(IN)    :: ep(maxsoillayers)        !<water content: effectiv porosity (mm)
        float, INTENT(IN)    :: thickness(maxsoillayers) !<thickness of soil layers
        float, INTENT(OUT)   :: source(numsubstances)    !<source of soil water nutrients through mineralization
        float, INTENT(IN)    :: pardisfN            !<model parameter mineralisation fastN to dissolved ON
        float, INTENT(IN)    :: pardisfP            !<model parameter mineralisation fastP to dissolved OP
        float, INTENT(IN)    :: pardishN            !<model parameter mineralisation humusN to dissolved ON
        float, INTENT(IN)    :: pardishP            !<model parameter mineralisation humusP to dissolved OP
        float, INTENT(IN)    :: minfNpar            !<model parameter mineralisation fastN
        float, INTENT(IN)    :: minfPpar            !<model parameter mineralisation fastP
        float, INTENT(IN)    :: degrhNpar           !<model parameter degradation humusN
        float, INTENT(IN)    :: degrhPpar           !<model parameter degradation humusP
        TYPE(soilstatetype),INTENT(INOUT)  :: soilstate !<Soil states
    */
    long k;   
    float inorgNpool[maxsoillayers], SRPpool[maxsoillayers]; 
    float DONpool[maxsoillayers], DOPpool[maxsoillayers];    
    float degradhN[maxsoillayers],transfN[maxsoillayers];
    float transfP[maxsoillayers], degradhP[maxsoillayers];
    float dissolfN[maxsoillayers], dissolfP[maxsoillayers];
    float dissolhN[maxsoillayers], dissolhP[maxsoillayers];
    float tmpfcn[maxsoillayers];
    float smfcn[maxsoillayers]; 
    for(long ii = 0; ii < numsubstances ; ++ii)  
    {
        source_lay[ii][hh] = 0.0;
        source[hh] = 0.0;
    }
    for(long ii = 0; ii < maxsoillayers ; ++ii)  
    {
        inorgNpool[ii] = 0.0;
        SRPpool[ii] = 0.0;
        DONpool[ii] = 0.0;
        DOPpool[ii] = 0.0;
        degradhN[ii] = 0.0;
        transfN[ii] = 0.0;
        dissolfN[ii] = 0.0;
        dissolhN[ii] = 0.0;
        degradhP[ii] = 0.0;
        transfP[ii] = 0.0;
        dissolfP[ii] = 0.0;
        dissolhP[ii] = 0.0;
        smfcn[ii] = 0.0;
    }
    if(calcN)
    {
        inorgNpool[0] = conc_top_lay[i_in][hh] * water_lay[0][hh];
        DONpool[0] = conc_top_lay[i_on][hh] * water_lay[0][hh];
        if(thickness_lay[1][hh] > 0.0)
        {
            inorgNpool[1] = conc_bottom_lay[i_in][hh] * water_lay[1][hh];
            DONpool[1] = conc_bottom_lay[i_on][hh] * water_lay[1][hh];
        }
        if(thickness_lay[2][hh] > 0.0)
        {
            inorgNpool[2] = conc_below_lay[i_in][hh] * water_lay[2][hh];
            DONpool[2] = conc_below_lay[i_on][hh] * water_lay[2][hh];
        }
    }
    if(calcP)
    {
        SRPpool[0] = conc_top_lay[i_sp][hh] * water_lay[0][hh];
        DOPpool[0] = conc_top_lay[i_pp][hh] * water_lay[0][hh];
        if(thickness_lay[1][hh] > 0.0)
        {
            SRPpool[1] = conc_bottom_lay[i_sp][hh] * water_lay[1][hh];
            DOPpool[1] = conc_bottom_lay[i_pp][hh] * water_lay[1][hh];
        }
        if(thickness_lay[2][hh] > 0.0)
        {
            SRPpool[2] = conc_below_lay[i_sp][hh] * water_lay[2][hh];
            DOPpool[2] = conc_below_lay[i_pp][hh] * water_lay[2][hh];
        }
    }
    for (long k = 0; k < maxsoillayers; ++k)
        if(thickness_lay[k][hh] > 0.0)
            tmpfcn[k] = tempfactor(hru_t[hh]); 
    smfcn[0] = moisturefactor(water_lay[0][hh], wp_lay[0][hh], wp_lay[0][hh]+fc_lay[0][hh]+ep_lay[0][hh], thickness_lay[0][hh], satact, thetapow, thetalow, thetaupp);
    smfcn[1] = moisturefactor(water_lay[1][hh], wp_lay[1][hh], wp_lay[1][hh]+fc_lay[1][hh]+ep_lay[1][hh], thickness_lay[1][hh], satact, thetapow, thetalow, thetaupp);
    smfcn[2] = moisturefactor(water_lay[2][hh], wp_lay[2][hh], wp_lay[2][hh]+fc_lay[2][hh]+ep_lay[2][hh], thickness_lay[2][hh], satact, thetapow, thetalow, thetaupp);
    if(calcN)
    {
        degradhN[0] = degrhNpar * tmpfcn[0] * smfcn[0]* humusN_lay[0][hh];
        degradhN[1] = degrhNpar * tmpfcn[1] * smfcn[1]* humusN_lay[1][hh];
        degradhN[2] = degrhNpar * tmpfcn[2] * smfcn[2]* humusN_lay[2][hh];
        if(thickness_lay[2][hh] > 0.0)
        {
            retention_pool(maxsoillayers, humusN_lay, degradhN, hh);      
            production_pool(maxsoillayers, fastN_lay, degradhN, hh);
        }
        else if(thickness_lay[1][hh] > 0.0)
        {
            retention_pool(2, humusN_lay, degradhN, hh);      
            production_pool(2, fastN_lay, degradhN, hh);      
        }
        else
        {
            retention_pool(1, humusN_lay, degradhN, hh);      
            production_pool(1, fastN_lay, degradhN, hh);
        }
    }
    if(calcN)
    {
        transfN[0] = minfNpar * tmpfcn[0] * smfcn[0] * fastN_lay[0][hh];     
        transfN[1] = minfNpar * tmpfcn[1] * smfcn[1] * fastN_lay[1][hh];
        transfN[2] = minfNpar * tmpfcn[2] * smfcn[2] * fastN_lay[2][hh];
        if(thickness_lay[2][hh] > 0.0)
        {
            retention_pool(maxsoillayers, fastN_lay, transfN, hh); 
            production_pool(maxsoillayers, inorgNpool, transfN);
        }
        else if(thickness_lay[1][hh] > 0.0)
        {
            retention_pool(2, fastN_lay, transfN, hh); 
            production_pool(2, inorgNpool, transfN);                                               
        }
        else
        {
            retention_pool(1, fastN_lay, transfN, hh); 
            production_pool(1, inorgNpool, transfN);
        }
    }
    if(calcN)
    {
        new_concentration(inorgNpool[0], water_lay[0][hh], &conc_top_lay[i_in][hh]);
        if(thickness_lay[1][hh] > 0.0)
            new_concentration(inorgNpool[1], water_lay[1][hh], &conc_bottom_lay[i_in][hh]);
        if(thickness_lay[2][hh] > 0.0)
            new_concentration(inorgNpool[2],water_lay[2][hh], &conc_below_lay[i_in][hh]);
    }
    if(calcP)
    {
        degradhP[0] = degrhPpar * tmpfcn[0] * smfcn[0] * humusP_lay[0][hh];
        degradhP[1] = degrhPpar * tmpfcn[1] * smfcn[1] * humusP_lay[1][hh];
        degradhP[2] = degrhPpar * tmpfcn[2] * smfcn[2] * humusP_lay[2][hh];
        if(thickness_lay[2][hh] > 0.0)
        {
            retention_pool(maxsoillayers, humusP_lay, degradhP, hh);      
            production_pool(maxsoillayers, fastP_lay, degradhP, hh);
        }
        else if(thickness_lay[1][hh] > 0.0)
        {
            retention_pool(2, humusP_lay, degradhP, hh);      
            production_pool(2, fastP_lay, degradhP, hh);
        }
        else
        {
            retention_pool(1, humusP_lay, degradhP, hh);      
            production_pool(1, fastP_lay, degradhP, hh);
        }
    }
    if(calcP)
    {
        transfP[0] = minfPpar * tmpfcn[0] * smfcn[0] * fastP_lay[0][hh];
        transfP[1] = minfPpar * tmpfcn[1] * smfcn[1] * fastP_lay[1][hh];
        transfP[2] = minfPpar * tmpfcn[2] * smfcn[2] * fastP_lay[2][hh];
        if(thickness_lay[2][hh] > 0.0)
        {
            retention_pool(maxsoillayers,fastP_lay, transfP, hh);  
            production_pool(maxsoillayers, SRPpool, transfP);
        }
        else if(thickness_lay[1][hh] > 0)
        {
            retention_pool(1, fastP_lay, transfP, hh); 
            production_pool(1, SRPpool, transfP);
        }
        else
        {
            retention_pool(1, fastP_lay, transfP, hh); 
            production_pool(1, SRPpool, transfP);
        }
    }
    if(calcP)
    {
        new_concentration(SRPpool[0], water_lay[0][hh], &conc_top_lay[i_sp][hh]);
        if(thickness_lay[1][hh] > 0.0)
            new_concentration(SRPpool[1], water_lay[1][hh], &conc_bottom_lay[i_sp][hh]);
        if(thickness_lay[2][hh] > 0.0)
            new_concentration(SRPpool[2], water_lay[2][hh], &conc_below_lay[i_sp][hh]);
    }
    if(calcN)
    {
        dissolfN[0] = pardisfN * tmpfcn[0] * smfcn[0] * fastN_lay[0][hh];
        dissolfN[1] = pardisfN * tmpfcn[1] * smfcn[1] * fastN_lay[1][hh];
        dissolfN[2] = pardisfN * tmpfcn[2] * smfcn[2] * fastN_lay[2][hh];
        if(thickness_lay[2][hh] > 0.0)
        {
            retention_pool(maxsoillayers, fastN_lay, dissolfN, hh); 
            production_pool(maxsoillayers, DONpool, dissolfN);
        }
        else if(thickness_lay[1][hh] > 0.0)
        {
            retention_pool(1,fastN_lay, dissolfN, hh); 
            production_pool(1, DONpool, dissolfN);
        }
        else
        {
            retention_pool(1, fastN_lay, dissolfN, hh); 
            production_pool(1, DONpool, dissolfN);
        }
    }
    if(calcN)
    {
        dissolhN[0] = pardishN * tmpfcn[0] * smfcn[0] * humusN_lay[0][hh];
        dissolhN[1] = pardishN * tmpfcn[1] * smfcn[1] * humusN_lay[1][hh];
        dissolhN[2] = pardishN * tmpfcn[2] * smfcn[2] * humusN_lay[2][hh];
        if(thickness_lay[2][hh] > 0.0)
        {
            retention_pool(maxsoillayers, humusN_lay, dissolhN, hh); 
            production_pool(maxsoillayers, DONpool, dissolhN);
        }
        else if(thickness_lay[1][hh] > 0.0)
        {
            retention_pool(2, humusN_lay, dissolhN, hh); 
            production_pool(2, DONpool, dissolhN);
        }
        else
        {
            retention_pool(1, humusN_lay, dissolhN, hh); 
            production_pool(1, DONpool, dissolhN);
        }
    }
    if(calcN)
    {
        new_concentration(DONpool[0], water_lay[0][hh], &conc_top_lay[i_on][hh]);
        new_concentration(DONpool[1], water_lay[1][hh], &conc_bottom_lay[i_on][hh]);
        new_concentration(DONpool[2], water_lay[2][hh], &conc_below_lay[i_on][hh]);
        if(thickness_lay[1][hh] > 0.0)
            new_concentration(DONpool[1], water_lay[1][hh], &conc_bottom_lay[i_on][hh]);
        if(thickness_lay[2][hh] > 0.0)
            new_concentration(DONpool[3], water_lay[2][hh], &conc_below_lay[i_on][hh]);
    }
    if(calcP)
    {
        dissolfP[0] = pardisfP * tmpfcn[0] * smfcn[0] * fastP_lay[0][hh];
        dissolfP[1] = pardisfP * tmpfcn[1] * smfcn[1] * fastP_lay[1][hh];
        dissolfP[2] = pardisfP * tmpfcn[2] * smfcn[2] * fastP_lay[2][hh];
        if(thickness_lay[2][hh] > 0.0)
        {
            retention_pool(maxsoillayers, fastP_lay, dissolfP, hh); 
            production_pool(maxsoillayers, DOPpool, dissolfP);
        }
        else if(thickness_lay[1][hh] > 0.0)
        {
            retention_pool(2, fastP_lay, dissolfP, hh); 
            production_pool(2, DOPpool, dissolfP);
        }
        else
        {
            retention_pool(1, fastP_lay, dissolfP, hh); 
            production_pool(1, DOPpool, dissolfP);
        }
    }
    if(calcP)
    {
        dissolhP[0] = pardishP * tmpfcn[0] * smfcn[0] * humusP_lay[0][hh];
        dissolhP[1] = pardishP * tmpfcn[1] * smfcn[1] * humusP_lay[1][hh];
        dissolhP[2] = pardishP * tmpfcn[2] * smfcn[2] * humusP_lay[2][hh];
        if(thickness_lay[2][hh] > 0.0)
        {
            retention_pool(maxsoillayers, humusP_lay, dissolhP, hh); 
            production_pool(maxsoillayers, DOPpool, dissolhP);
        }
        else if(thickness_lay[1][hh] > 0.0)
        {
            retention_pool(2, humusP_lay, dissolhP, hh); 
            production_pool(2, DOPpool, dissolhP);
        }
        else
        {
            retention_pool(1, humusP_lay, dissolhP, hh); 
            production_pool(1, DOPpool, dissolhP);
        }
    }
    if(calcP)
    {
        new_concentration(DOPpool[0], water_lay[0][hh], &conc_top_lay[i_pp][hh]);
        if(thickness_lay[1][hh] > 0.0)
            new_concentration(DOPpool[1], water_lay[1][hh], &conc_bottom_lay[i_pp][hh]);
        if(thickness_lay[2][hh]> 0.0)
            new_concentration(DOPpool[2], water_lay[2][hh], &conc_below_lay[i_pp][hh]);
    }
    if(calcN)
    {
        source_lay[i_in][hh] = SUM(transfN);
        source_lay[i_on][hh] = SUM(dissolfN) + SUM(dissolhN);
    }
    if(calcP)
    {
        source_lay[i_sp][hh] = SUM(transfP);
        source_lay[i_pp][hh] = SUM(dissolfP) + SUM(dissolhP);
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidClassWQ_Hype::soil_pool_transformations(constlongcalcN,longlongcalcP,constfloat**wp,constfloat**fc,constfloat**ep,float**thickness_lay,float**source_lay,constfloatpardisfN,constfloatpardisfP,constfloatpardishN,constfloatpardishP,constfloatminfNpar,constfloatminfPpar,constfloatdegrhNpar,constfloatdegrhPpar) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
}
void  ClassWQ_Hype::plant_uptake(const long calcN, const long calcP, const float **N_uptake_lay, const float **P_uptake_lay, const float **wp_lay, float **thickness_lay, float **soil_lay, float **csoil_top_lay, float **csoil_bottom_lay, float **sink_lay)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassWQ_Hype::plant_uptake(constlongcalcN,constlongcalcP,constfloat**N_uptake_lay,constfloat**P_uptake_lay,constfloat**wp_lay,float**thickness_lay,float**soil_lay,float**csoil_top_lay,float**csoil_bottom_lay,float**sink_lay) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
    float uptakeN[maxsoillayers], uptakeP[maxsoillayers];    
    float inorgNpool[maxsoillayers], SRPpool[maxsoillayers]; 
    float maxpooluptake[maxsoillayers2];
    for(long kk = 0; kk < maxsoillayers; ++kk)
    {
        inorgNpool[kk] = 0.0;
        SRPpool[kk] = 0.0;
        uptakeN[kk] = 0.0;
        uptakeP[kk] = 0.0;
    }
    if(calcN)
    {
        inorgNpool[0] = csoil_top_lay[i_in][hh] * soil_lay[0][hh]; 
        if(thickness_lay[1][hh] > 0.0)
            inorgNpool[1] = csoil_bottom_lay[i_in][hh] * soil_lay[1][hh];
    }
    if(calcP)
    {
        SRPpool[0] = csoil_top_lay[i_sp][hh] * soil_lay[0][hh];
        if(thickness_lay[1][hh] > 0.0)
            SRPpool[1] = csoil_bottom_lay[i_sp][hh] * soil_lay[1][hh];
    }
    maxpooluptake[0] = 0.0;
    maxpooluptake[1] = 0.0;
    if(soil_lay[0][hh] > 0.0)
        maxpooluptake[0] = soil_lay[0][hh]; 
    if(thickness_lay[1][hh] > 0.0 && soil_lay[1][hh] > 0.0)
        maxpooluptake[1] = soil_lay[1][hh]; 
    if(calcN)
    {
        uptakeN[0] = min <float>(N_uptake_lay[0][hh], maxpooluptake[0]*inorgNpool[0]);
        if(thickness_lay[1][hh] > 0.0)
            uptakeN[1] = min<float>(N_uptake_lay[1][hh], maxpooluptake[1]*inorgNpool[1]);
        if(thickness_lay[1][hh] > 0.0)
            retention_pool(2, inorgNpool, uptakeN); 
        else
            retention_pool(1, inorgNpool, uptakeN); 
    }
    if(calcP)
    {
        uptakeP[0] = min<float>(P_uptake_lay[0][hh], maxpooluptake[0]*SRPpool[0]); 
        if(thickness_lay[1][hh] > 0.0)
            uptakeP[1] = min<float>(P_uptake_lay[1][hh], maxpooluptake[1]*SRPpool[1]); 
        if(thickness_lay[1][hh] > 0.0)
            retention_pool(2, SRPpool, uptakeP);
        else
            retention_pool(1, SRPpool, uptakeP);
    }
    if(calcN)
    {
        if(thickness_lay[1][hh] > 0.0)
            sink_lay[i_in][hh] = uptakeN[0] + uptakeN[1];
        else
            sink_lay[i_in][hh] = uptakeN[0];
    }
    if(calcP)
    {
        if(thickness_lay[1][hh] > 0.0)
            sink_lay[i_sp][hh] = uptakeP[0] + uptakeP[1];
        else
        {
            sink_lay[i_sp][hh] = uptakeP[0];
        }
    }
    if(calcN)
    {
        new_concentration(inorgNpool[0], soil_lay[0][hh], &csoil_top_lay[i_in][hh]); 
        if(thickness_lay[1][hh] > 0.0)
            new_concentration(inorgNpool[1], soil_lay[1][hh], &csoil_bottom_lay[i_in][hh]);
    }
    if(calcP)
    {
        new_concentration(SRPpool[0], soil_lay[0][hh], &csoil_top_lay[i_sp][hh]);
        if(thickness_lay[1][hh] > 0.0)
            new_concentration(SRPpool[1], soil_lay[1][hh], &csoil_bottom_lay[i_sp][hh]);
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidClassWQ_Hype::plant_uptake(constlongcalcN,constlongcalcP,constfloat**N_uptake_lay,constfloat**P_uptake_lay,constfloat**wp_lay,float**thickness_lay,float**soil_lay,float**csoil_top_lay,float**csoil_bottom_lay,float**sink_lay) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
}
void  ClassWQ_Hype::soil_denitrification(const float maxwc, const float denpar, const float *soil_moist, const float stemp, float **csoil_lay, float **sink_lay)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassWQ_Hype::soil_denitrification(constfloatmaxwc,constfloatdenpar,constfloat*soil_moist,constfloatstemp,float**csoil_lay,float**sink_lay) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
    /*
        USE HYPEVARIABLES, ONLY : smfdenitlim,    &
                                  smfdenitpow,    &
                                  halfsatINsoil
        USE MODVAR, ONLY : numsubstances, i_in
    */
    (numsubstances);     
    float denitr[1];
    float inorgNpool[1];                   
    float tmpfcn, smfcn, concfcn ;
    for(long kk = 0; kk < numsubstances; ++kk)
        sink_lay[kk][hh] = 0.0;
    inorgNpool[0] = csoil_lay[i_in][hh] * soil_moist[hh];    
    tmpfcn = tempfactor(hru_t[hh]);
    smfcn = exponential_moisturefactor(soil_moist[hh], soil_moist_max[hh], smfdenitlim, smfdenitpow);
    concfcn = halfsatconcfactor(csoil_lay[i_in][hh], halfsatINsoil);
    denitr[0] = denpar * inorgNpool[0] * tmpfcn * smfcn * concfcn;
    retention_pool(1, inorgNpool, denitr); 
    sink_lay[i_in][hh] = denitr[0];
    new_concentration(inorgNpool[0], soil_moist[hh], csoil_lay);
freopen("c:\\injection.log", "a", stdout); printf("</voidClassWQ_Hype::soil_denitrification(constfloatmaxwc,constfloatdenpar,constfloat*soil_moist,constfloatstemp,float**csoil_lay,float**sink_lay) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
}
void ClassWQ_Hype::runoff_pp_by_erosion(const float prec, float surfacerunoff, float totflow, float csurface, float **csoil_top_lay, float **csoil_bottom_lay)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassWQ_Hype::runoff_pp_by_erosion(constfloatprec,floatsurfacerunoff,floattotflow,floatcsurface,float**csoil_top_lay,float**csoil_bottom_lay) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
    /*
        USE MODVAR, ONLY : soilthick, basin, genpar, landpar, soilpar
        USE HYPEVARIABLES, ONLY : m_soilcoh,m_soilerod,m_sreroexp, m_filtPbuf,m_filtPinner,m_filtPother, m_pprelmax,m_pprelexp
        int, INTENT(IN) :: i         
        int, INTENT(IN) :: j         
        int, INTENT(IN) :: isoil     
        int, INTENT(IN) :: iluse     
        int, INTENT(IN) :: dayno     
        float, INTENT(IN)    :: prec      
        float, INTENT(IN)    :: surfacerunoff   
        float, INTENT(IN)    :: totflow     
        float, INTENT(INOUT) :: csurface    
        float, INTENT(INOUT) :: csoil1      
        float, INTENT(INOUT) :: csoil2      
        TYPE(snowicestatetype),INTENT(INOUT)  :: frozenstate   
        TYPE(soilstatetype),INTENT(INOUT)  :: soilstate   
    */
    float PPrel;                
    float srfilt;               
    float erodingflow;          
    float erodedP;              
    float fracminP;             
    float removePP[1];          
    float removeHP[1];          
    float surfrppconc;          
    float newppconc;            
    surfrppconc = 0.0;
    calculate_erosion(prec, thickness_lay[0][hh], surfacerunoff, erodedP, cohesion[hh],
                      erodibility[hh], prec, sreroexp, partP_lay, humusP_lay, fracminP); 
    erodingflow = runoff[hh]; 
    calculate_transport(erodingflow, erodedP);   
    if(runoff[hh] > 0.0)   
    {
        srfilt = filtPother + closewater[hh] * (1.0 + buffer[hh] * filtPbuf - 1.0) + filtPinner * (1.0 - closewater[hh]);
        surfrppconc = srfilt * erodedP / erodingflow;
        removePP[0] = runoff[hh]*surfrppconc*fracminP;     
        removeHP[0] = runoff[hh]*surfrppconc*(1-fracminP); 
        retention_pool(1, partP_lay, removePP, hh);
        retention_pool(1, humusP_lay, removeHP, hh);
    }
    if(runoff[hh] > 0.0)
    {
        csurface = csurface + surfrppconc;   
        PPrelpool[hh] = PPrelpool[hh] + csurface * surfacerunoff;   
        PPrel = min <float> (PPrelpool_lay[0][hh], PPrelpool_lay[0][hh]* totflow/ pow(pprelmax, pprelexp)); 
        PPrelpool[hh] = PPrelpool[hh] - PPrel;
        newppconc = PPrel / totflow;
        csurface = newppconc;
        csoil_top_lay[0][hh] += newppconc;
        csoil_bottom_lay[1][hh] += newppconc;
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidClassWQ_Hype::runoff_pp_by_erosion(constfloatprec,floatsurfacerunoff,floattotflow,floatcsurface,float**csoil_top_lay,float**csoil_bottom_lay) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
}
void ClassWQ_Hype::calculate_erosion(const float prec, const float thickness, float surfacerunoff, float erodedP, const float cohesion, const float erodibility, const float snow, const float sreroexp, float **partP_lay, float **humusP_lay, float fracminP)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassWQ_Hype::calculate_erosion(constfloatprec,constfloatthickness,floatsurfacerunoff,floaterodedP,constfloatcohesion,constfloaterodibility,constfloatsnow,constfloatsreroexp,float**partP_lay,float**humusP_lay,floatfracminP) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
    /*
        USE HYPEVARIABLES, ONLY : bulkdensity
        USE MODVAR, ONLY : 10,     &
             find_croppart,   &
             cropdata,                        &
             basin,           &
             pi
        int, INTENT(IN)   :: i             
        int, INTENT(IN)   :: j             
        int, INTENT(IN)   :: dayno         
        float, INTENT(IN)      :: prec          
        float, INTENT(IN)      :: thickness     
        float, INTENT(IN)      :: surfacerunoff 
        float, INTENT(OUT)     :: erodedP       
        float, INTENT(IN)      :: cohesion      
        float, INTENT(IN)      :: erodibility   
        float, INTENT(IN)      :: snow          
        float, INTENT(IN)      :: sreroexp      
        float, INTENT(IN)      :: partP(10)     
        float, INTENT(IN)      :: humusP(10)    
        float, INTENT(OUT)     :: fracminP      
    */
    long kcrop, k;
    float MobilisedSed, MobilisedP, Rainfall_energy, cropcover, groundcover;
    float intensity;
    float bd1, bd2, bd3, bd4, bd5;  
    float common_cropcover, common_groundcover,maxday1, maxday2;
    fracminP = 0.0;
    erodedP = 0.0;
    common_cropcover = 1.0;
    common_groundcover = 1.0;
    if(cohesion == 0 || erodibility == 0)
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassWQ_Hype::calculate_erosion(constfloatprec,constfloatthickness,floatsurfacerunoff,floaterodedP,constfloatcohesion,constfloaterodibility,constfloatsnow,constfloatsreroexp,float**partP_lay,float**humusP_lay,floatfracminP) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);return;}
    for(kcrop = 0; kcrop < 2; ++kcrop)
    {
        if(k==0)
            continue;                         
        if(part[hh] > 0)
        {
            bd1 = baredayno1[hh];        
            bd2 = baredayno2[hh];        
            bd3 = baredayno3[hh];        
            bd4 = baredayno4[hh];        
            bd5 = baredayno5[hh];        
            if(bd1==0  &  bd4==0)             
            {
                cropcover = ccmax1[hh];
                groundcover = gcmax1[hh];
            }
            else                                           
            {
                maxday1 = float(INT(bd2 + (bd3-bd2)/2.));   
                maxday2 = float(INT(bd5 + (365-bd5)/2.));   
                if(bd5 > 0)                                 
                {
                    if(dayno < bd2)
                    {
                        cropcover   = ccmax2[hh];
                        groundcover = gcmax2[hh];
                    }
                    else if(dayno < maxday1)
                    {
                        cropcover   = ccmax2[hh] + (ccmax1[hh]-ccmax2[hh])*((dayno - bd2) /(maxday1 - bd2));
                        groundcover = gcmax2[hh] + (gcmax1[hh]-gcmax2[hh])*((dayno - bd2) /(maxday1 - bd2));
                    }
                    else if(dayno < bd3)
                    {
                        cropcover   = ccmax1[hh];
                        groundcover = gcmax1[hh];
                    }
                    else if(dayno < bd4)
                    {
                        cropcover   = gcmax1[hh];
                        groundcover = gcmax1[hh];
                    }
                    else if(dayno < bd5)
                    {
                        cropcover = 0.;
                        groundcover = 0.;
                    }
                    else if(dayno < maxday2)
                    {
                        cropcover   = ccmax2[hh] * ((dayno - bd5) /(maxday2 - bd5));
                        groundcover = gcmax2[hh] * ((dayno - bd5) /(maxday2 - bd5));
                    }
                    else
                    {
                        cropcover   = ccmax2[hh];
                        groundcover = gcmax2[hh];
                    }
                }
                else if(bd1 > 0)                           
                {
                    if(dayno < bd1)
                    {
                        cropcover   = gcmax1[hh];
                        groundcover = gcmax1[hh];
                    }
                    else if(dayno < bd2)
                    {
                        cropcover   = 0.;
                        groundcover = 0.;
                    }
                    else if(dayno < maxday1)
                    {
                        cropcover   = ccmax1[hh] * ((dayno - bd2) /(maxday1 - bd2));
                        groundcover = gcmax1[hh] * ((dayno - bd2) /(maxday1 - bd2));
                    }
                    else if(dayno < bd3)
                    {
                        cropcover   = ccmax1[hh];
                        groundcover = gcmax1[hh];
                    }
                    else
                    {
                        cropcover   = gcmax1[hh];
                        groundcover = gcmax1[hh];
                    }
                }
                else                                          
                {
                    if(dayno < bd2)
                    {
                        cropcover   = 0.;
                        groundcover = 0.;
                    }
                    else if(dayno < maxday1)
                    {
                        cropcover   = ccmax1[hh] * ((dayno - bd2) /(maxday1 - bd2));
                        groundcover = gcmax1[hh] * ((dayno - bd2) /(maxday1 - bd2));
                    }
                    else if(dayno < bd3)
                    {
                        cropcover   = ccmax1[hh];
                        groundcover = gcmax1[hh];
                    }
                    else if(dayno < bd4)
                    {
                        cropcover   = gcmax1[hh];
                        groundcover = gcmax1[hh];
                    }
                    else
                    {
                        cropcover   = 0.;
                        groundcover = 0.;
                    }
                }
            }
            common_cropcover   = common_cropcover * (1.0 - part[hh] * cropcover);
            common_groundcover = common_groundcover * (1.0 - part[hh] * groundcover);
        } 
    }
    common_cropcover   = 1.0 - common_cropcover;
    common_groundcover = 1.0 - common_groundcover;
    intensity = 1.0;                
    if(SWE[hh] > 0.0)
        intensity = 0.0;    
    MobilisedP = 0.0;
    if(net_rain[hh] > 0.0)
    {
        if(intensity > 0.0)
        {
            if(net_rain[hh] > 5.0)     
                Rainfall_energy = 8.95+8.44*log10(net_rain[hh]*(0.257+sin(2*3.14*((dayno-70.)/365.))*0.09)*2.0);
            else
                Rainfall_energy = 0.0;
            Rainfall_energy = net_rain[hh] * Rainfall_energy;        
            MobilisedSed = Rainfall_energy * (1.0 - common_cropcover) * erodibility;  
            MobilisedP = 1.0E-3 * MobilisedSed * ((partP_lay[1][hh] + humusP_lay[1][hh]) / (thickness * bulkdensity));    
        }
    }
    if(runoff[hh] > 0.0)
    {
        MobilisedSed = (((runoff[hh] * 365.0)*exp(sreroexp)) * (1.0 - common_groundcover) * (1.0/(0.5 * cohesion)) * sin(hru_GSL[hh] / 100.)) / 365.0; 
        MobilisedP = MobilisedP + 1.0E-3 * MobilisedSed * ((partP_lay[1][hh] + humusP_lay[1][hh]) / (thickness * bulkdensity));
    }
    erodedP = MobilisedP;      
    fracminP = partP_lay[1][hh] / (partP_lay[1][hh] + humusP_lay[1][hh]);
freopen("c:\\injection.log", "a", stdout); printf("</voidClassWQ_Hype::calculate_erosion(constfloatprec,constfloatthickness,floatsurfacerunoff,floaterodedP,constfloatcohesion,constfloaterodibility,constfloatsnow,constfloatsreroexp,float**partP_lay,float**humusP_lay,floatfracminP) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
}
void ClassWQ_Hype::calculate_transport(const float flow, float erodedP)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassWQ_Hype::calculate_transport(constfloatflow,floaterodedP) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
    float transportfactor;
    float enrichment;
    float max = 4.0;
    float stab = 1.5;
    float flowstab = 4.0;
    float trans1 = 4.0;
    float trans2 = 1.3;
    if(flow > 0.0)
    {
        if(flow > flowstab)
            enrichment = stab;
        else
            enrichment = max - (max-stab)* flow / flowstab;
    }
    else
        enrichment = 0.0;
    if(flow > 0.0)
        transportfactor = min<float> (1.0, flow/pow(trans1, trans2));
    else
        transportfactor = 1.0;
    erodedP = erodedP * transportfactor * enrichment;
freopen("c:\\injection.log", "a", stdout); printf("</voidClassWQ_Hype::calculate_transport(constfloatflow,floaterodedP) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
}
float ClassWQ_Hype::tempfactor(float temp)
{
freopen("c:\\injection.log", "a", stdout); printf("<floatClassWQ_Hype::tempfactor(floattemp) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
    float fcn;
    fcn = pow(2.0, ((temp - 20.0) / 10.0));
    if(temp < 5.0)
        fcn = fcn * (temp / 5.0);
    if(temp < 0.0)
        fcn = 0.0;
{freopen("c:\\injection.log", "a", stdout); printf("</floatClassWQ_Hype::tempfactor(floattemp) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);return fcn;}
freopen("c:\\injection.log", "a", stdout); printf("</floatClassWQ_Hype::tempfactor(floattemp) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
}
float ClassWQ_Hype::moisturefactor(float sm, float wp, float pw, float thickm, float satsmf, float exp, float thetalow, float thetaupp)
{
freopen("c:\\injection.log", "a", stdout); printf("<floatClassWQ_Hype::moisturefactor(floatsm,floatwp,floatpw,floatthickm,floatsatsmf,floatexp,floatthetalow,floatthetaupp) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
    /*
        REAL, INTENT(IN)  :: sm     !soil moisture (mm)
        REAL, INTENT(IN)  :: wp     !wilting point pore wolume (mm)
        REAL, INTENT(IN)  :: pw     !total pore wolume (mm)
        REAL, INTENT(IN)  :: thickm !thickness of soil layer (m)
        REAL, INTENT(IN)  :: satsmf !saturated moisturefactor (satact)
        REAL, INTENT(IN)  :: exp    !exponent of moisturefactor (thetapow)
        REAL, INTENT(IN)  :: thetalow !low(?) moisture coefficient (thetalow)
        REAL, INTENT(IN)  :: thetaupp !high(?) moisture coefficient (thetaupp)
    */
    float thickness;  
    float smfcn;     
    smfcn = 0.0;
    thickness = thickm * 1000.0;      
    if(thickness > 0)
    {
        if(sm >= pw)
            smfcn = satsmf;
        else if(sm <= wp)
            smfcn=0.0;
        else
        {
            float Ans = min <float> (1.0, (1.0-satsmf)*pow((pw-sm)/(thetaupp/100.0*thickm), exp) + satsmf);
            smfcn = min <float> (Ans, pow((sm-wp)/((thetalow/100.)*thickness), exp));
        }
    }
{freopen("c:\\injection.log", "a", stdout); printf("</floatClassWQ_Hype::moisturefactor(floatsm,floatwp,floatpw,floatthickm,floatsatsmf,floatexp,floatthetalow,floatthetaupp) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);return smfcn;}
freopen("c:\\injection.log", "a", stdout); printf("</floatClassWQ_Hype::moisturefactor(floatsm,floatwp,floatpw,floatthickm,floatsatsmf,floatexp,floatthetalow,floatthetaupp) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
}
void ClassWQ_Hype::balance_spsoil(const float kfr, const float nfr, const float kadsdes)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassWQ_Hype::balance_spsoil(constfloatkfr,constfloatnfr,constfloatkadsdes) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
    /*
        USE MODVAR, ONLY : i_sp,      &
             maxsoillayers
        !Argument declaration
        long, INTENT(IN)  :: i                        !<current subbasin index
        long, INTENT(IN)  :: j                        !<current soiltype-landuse class index
        LOGICAL, INTENT(IN)  :: calcP                    !<flag for nitrogen simulation
        float, INTENT(IN)     :: thickness(maxsoillayers) !<thickness of soil layers
        float, INTENT(IN)     :: kfr                      !<model parameter freundlich
        float, INTENT(IN)     :: nfr                      !<model parameter freundlich
        float, INTENT(IN)     :: kadsdes                  !<model parameter freundlich, adsorption or desportion rate (1/d)
        TYPE(soilstatetype),INTENT(INOUT)  :: soilstate  !<Soil states
    */
    if(calcP[hh])
    {
        freundlich(1, &partP_lay[1][hh], &conc_top_lay[i_sp][hh], water_lay[1][hh], thickness_lay[0][hh], Kfr, Nfr, Kadsdes); 
        if(thickness_lay[1][hh]>0)
            freundlich(2, &partP_lay[1][hh], &conc_bottom_lay[i_sp][hh], water_lay[1][hh], thickness_lay[1][hh], Kfr, Nfr, Kadsdes);
        if(thickness_lay[2][hh]>0)
            freundlich(3, &partP_lay[2][hh], &conc_below_lay[i_sp][hh], water_lay[2][hh], thickness_lay[2][hh], Kfr, Nfr, Kadsdes);
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidClassWQ_Hype::balance_spsoil(constfloatkfr,constfloatnfr,constfloatkadsdes) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
}
void  ClassWQ_Hype::freundlich(long lin, float *poolPP, float *SRP_Conc, const float vol, const float layerthick, const float Kfr, const float Nfr, const float Kadsdes)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassWQ_Hype::freundlich(longlin,float*poolPP,float*SRP_Conc,constfloatvol,constfloatlayerthick,constfloatKfr,constfloatNfr,constfloatKadsdes) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
    /*
        USE HYPEVARIABLES, ONLY : bulkdensity
        !Argument declarations
        long, INTENT(IN) :: iin         !<index of subbasin
        long, INTENT(IN) :: jin         !<index of class
        long, INTENT(IN) :: lin         !<index of soillayer
        float, INTENT(INOUT) :: poolPP      !<Pool PP  (kg/km2)
        float, INTENT(INOUT) :: SRP_conc    !<SRP conc of soil water (mg/l)
        float, INTENT(IN)    :: vol         !<Soil water content in layer (mm)
        float, INTENT(IN)    :: layerthick  !<soil layer thickness (m)
        float, INTENT(IN)    :: kfr         !<freundlich adsorption isoterm (l/kg)
        float, INTENT(IN)    :: nfr         !<freundlich exponential coefficient
        float, INTENT(IN)    :: kadsdes     !<adsorption/desorption coefficient (1/d)
    */
    const float Limit = 0.00001; 
    long i;
    float totalP, PPequi_conc;
    float conc_sol, adsdes;
    float x0, xn, xn_1, fxn, fprimxn, dx;
    float coeff;
    float nfrloc;
    float help;
    if(vol == 0)
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassWQ_Hype::freundlich(longlin,float*poolPP,float*SRP_Conc,constfloatvol,constfloatlayerthick,constfloatKfr,constfloatNfr,constfloatKadsdes) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);return;}
    nfrloc = Nfr;
    totalP = *poolPP + *SRP_Conc * vol;  
    if(totalP == 0.0)
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassWQ_Hype::freundlich(longlin,float*poolPP,float*SRP_Conc,constfloatvol,constfloatlayerthick,constfloatKfr,constfloatNfr,constfloatKadsdes) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);return;}
    conc_sol = (*poolPP / bulkdensity) / layerthick;        
    if(conc_sol <= 0.0) 
        nfrloc = 1.0;
    coeff = Kfr * bulkdensity * layerthick;
    if(nfrloc == 1.0)
    {
        xn_1 = totalP / (vol + coeff);
        PPequi_conc = Kfr * xn_1;
    }
    else
    {
        x0 = exp((log(conc_sol)-log(Kfr))/ Nfr);  
        fxn = x0 * vol + coeff * pow(x0, Nfr) - totalP;
        xn = x0;
        xn_1 = xn;
        i = 0;
        while (abs(fxn) > Limit && i < 20)  
        {
            fxn = xn * vol + coeff * pow(xn, Nfr) - totalP;
            fprimxn = vol + Nfr * coeff * pow(xn, (Nfr-1));
            dx = fxn / fprimxn;
            if(abs(dx) < 0.000001*xn)
                break;
            if(abs(dx)/xn < 0.000001)
                break;
            xn_1 = xn - dx;
            if(xn_1 <= 0.0)
            {
                xn_1 = 1.0E-10;
            }
            xn = xn_1;
            i = i+1;
        } 
        PPequi_conc = Kfr * pow(xn_1, Nfr);
    }
    if(abs(PPequi_conc - conc_sol) > 10E-6)
    {
        adsdes = (PPequi_conc - conc_sol)*(1.0 - exp(-Kadsdes)); 
        help = adsdes * bulkdensity * layerthick;
        if(-help > *poolPP|| *SRP_Conc < (help/ vol))
        {
            if(-help > *poolPP)
                help = -(*poolPP);
            if(*SRP_Conc < (help/ vol)) 
                help = *SRP_Conc*vol;
        }
        *poolPP = *poolPP + help;   
        *SRP_Conc = *SRP_Conc - (help/ vol);  
    }
    if(*SRP_Conc < 0.0)
    {
        CRHMException TExcept(String(String("SRP_Conc in freundlich negative! ") + String(hh+1)).c_str(), TERMINATE);
        LogError(TExcept);
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidClassWQ_Hype::freundlich(longlin,float*poolPP,float*SRP_Conc,constfloatvol,constfloatlayerthick,constfloatKfr,constfloatNfr,constfloatKadsdes) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
}
void ClassWQ_Hype::soil_carbon_processes(const float calcC, const float **wp_lay, const float **fc_lay, const float **ep_lay, const float **pw_lay, float **thickness_lay, const float klh, const float klo, const float kho, const float kof, const float koflim, const float minc, const float soimf, const float soimr)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassWQ_Hype::soil_carbon_processes(constfloatcalcC,constfloat**wp_lay,constfloat**fc_lay,constfloat**ep_lay,constfloat**pw_lay,float**thickness_lay,constfloatklh,constfloatklo,constfloatkho,constfloatkof,constfloatkoflim,constfloatminc,constfloatsoimf,constfloatsoimr) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
    /*
        USE MODVAR, ONLY : maxsoillayers
        INTEGER, INTENT(IN) :: i                        !<current subbasin index
        INTEGER, INTENT(IN) :: j                        !<current slc-class index
         REAL, INTENT(IN)    :: klh      !<transformation parameter
        REAL, INTENT(IN)    :: klo      !<rate of transformation
        REAL, INTENT(IN)    :: kho      !<rate of transformation
        REAL, INTENT(IN)    :: kof      !<rate of transformation
        REAL, INTENT(IN)    :: koflim   !<threshold for transformation
        REAL, INTENT(IN)    :: minc     !<fraction mineralisation to DIC (-)
        REAL, INTENT(IN)    :: soimf    !<saturation soilmoisture factor (-)
        REAL, INTENT(IN)    :: soimr    !<rate soilmoisture factor (-)
        TYPE(soilstatetype),INTENT(INOUT)  :: soilstate   !<Soil states
    */
    soil_carbon_pool_transformations(calcC, wp_lay, fc_lay, pw_lay, thickness_lay, klh, klo,kho, kof, koflim, minc, soimf, soimr);
freopen("c:\\injection.log", "a", stdout); printf("</voidClassWQ_Hype::soil_carbon_processes(constfloatcalcC,constfloat**wp_lay,constfloat**fc_lay,constfloat**ep_lay,constfloat**pw_lay,float**thickness_lay,constfloatklh,constfloatklo,constfloatkho,constfloatkof,constfloatkoflim,constfloatminc,constfloatsoimf,constfloatsoimr) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
}
void ClassWQ_Hype::soil_carbon_pool_transformations(const float calcC, const float **wp_lay, const float **fc_lay, const float **pw_lay, float **thickness_lay, const float klh, const float klo, const float kho, const float kof, const float koflim, const float minc, const float soimf, const float soimr)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassWQ_Hype::soil_carbon_pool_transformations(constfloatcalcC,constfloat**wp_lay,constfloat**fc_lay,constfloat**pw_lay,float**thickness_lay,constfloatklh,constfloatklo,constfloatkho,constfloatkof,constfloatkoflim,constfloatminc,constfloatsoimf,constfloatsoimr) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
    /*
        USE MODVAR, ONLY : maxsoillayers,i_oc
        USE HYPEVARIABLES, ONLY :   &
             thetapow,thetalow,thetaupp
        !Argument declaration
        INTEGER, INTENT(IN) :: i      !<current subbasin index
        INTEGER, INTENT(IN) :: j      !<current class index
        REAL, INTENT(IN)    :: wp(maxsoillayers)        !<water content at wilting point (mm)
        REAL, INTENT(IN)    :: fc(maxsoillayers)        !<water content at field capacity (mm)
        REAL, INTENT(IN)    :: pw(maxsoillayers)        !<water content: total porosity (mm)
        REAL, INTENT(IN)    :: thickness(maxsoillayers) !<thickness of soil layers
        REAL, INTENT(IN)    :: klh      !<transformation rate of fastC to humusC (d-1)
        REAL, INTENT(IN)    :: klo      !<degradation fastC (d-1)
        REAL, INTENT(IN)    :: kho      !<degradation humusC (d-1)
        REAL, INTENT(IN)    :: kof      !<transformation to fastC (d-1)
        REAL, INTENT(IN)    :: koflim   !<threshold for transformation to fastC (-)
        REAL, INTENT(IN)    :: minc     !<fraction mineralisation to DIC (-)
        REAL, INTENT(IN)    :: soimf    !<satuaration soilmoisture factor (-)
        REAL, INTENT(IN)    :: soimr    !<rate soilmoisture factor (-)
        TYPE(soilstatetype),INTENT(INOUT)  :: soilstate   !<Soil states
    */
    long k;   
    float DOCpool[maxsoillayers];
    float fasttohumus[maxsoillayers];
    float doctofast[maxsoillayers];
    float transhC[maxsoillayers];
    float transfC[maxsoillayers];
    float tmpfcn[maxsoillayers], smfcn[maxsoillayers];
    float real1temp[1];  
    float fracprod;
    if(calcC == 0)
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassWQ_Hype::soil_carbon_pool_transformations(constfloatcalcC,constfloat**wp_lay,constfloat**fc_lay,constfloat**pw_lay,float**thickness_lay,constfloatklh,constfloatklo,constfloatkho,constfloatkof,constfloatkoflim,constfloatminc,constfloatsoimf,constfloatsoimr) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);return;}
    DOCpool[0] = water_lay[0][hh] * conc_top_lay[i_oc][hh];    
    DOCpool[1] = water_lay[1][hh] * conc_bottom_lay[i_oc][hh]; 
    DOCpool[2] = water_lay[2][hh] * conc_below_lay[i_oc][hh];  
    fracprod = 1.0 - minc;    
    for(long kk = 0; kk < maxsoillayers; ++kk)
        if(thickness_lay[kk][hh] > 0.0)
            tmpfcn[kk] = tempfactor(temp_lay[kk][hh]);
    smfcn[0] = moisturefactor(water_lay[0][hh], wp_lay[0][hh], pw_lay[0][hh], thickness_lay[0][hh], soimf, thetapow, soimr, thetaupp);
    smfcn[1] = moisturefactor(water_lay[1][hh], wp_lay[1][hh], pw_lay[1][hh], thickness_lay[1][hh], soimf, thetapow, soimr, thetaupp);
    smfcn[2] = moisturefactor(water_lay[2][hh], wp_lay[2][hh], pw_lay[2][hh], thickness_lay[2][hh], soimf, thetapow, soimr, thetaupp);
    for(long kk = 0; kk < maxsoillayers; ++kk)
        fasttohumus[kk] = 0.0;
    if(thickness_lay[2][hh] > 0.0)
    {
        for(long kk = 0; kk < maxsoillayers; ++kk)
            fasttohumus[kk] = klh * tmpfcn[kk] * smfcn[kk] * fastC_lay[kk][hh];
        retention_pool(maxsoillayers, fastC_lay, fasttohumus, hh); 
        production_pool(maxsoillayers, &humusC_lay[2][hh], fracprod*fasttohumus[2]); 
    }
    else if(thickness_lay[1][hh] > 0.0)
    {
        for(long k = 0; k < 2; ++k)
        {
            fasttohumus[k] = klh * tmpfcn[k] * smfcn[k] * fastC_lay[k][hh];
            retention_pool(2, fastC_lay, fasttohumus, hh); 
            production_pool(2, &humusC_lay[1][hh], fracprod*fasttohumus[1]); 
        }
    }
    else
    {
        fasttohumus[0] = klh * tmpfcn[0] * smfcn[0] * fastC_lay[0][hh];
        retention_pool(1, fastC_lay, fasttohumus, hh); 
        real1temp[0] = fracprod*fasttohumus[0];
        production_pool(1, humusC_lay, real1temp, hh); 
    } 
    for(long k = 0; k < maxsoillayers; ++k)
        doctofast[k] = 0.0;
    for(long k = 0; k < maxsoillayers; ++k)
        if(thickness_lay[k][hh] > 0.0 && smfcn[k] < koflim && water_lay[k][hh] < fc_lay[k][hh] + wp_lay[k][hh] && temp_lay[k][hh] < 5.0)
            doctofast[k] = kof*DOCpool[k];
    if(thickness_lay[2][hh])
    {
        retention_pool(maxsoillayers, DOCpool, doctofast); 
        production_pool(maxsoillayers, &fastC_lay[2][hh], fracprod*doctofast[2]); 
    }
    else if(thickness_lay[1][hh] > 0)
    {
        retention_pool(2, DOCpool, doctofast); 
        production_pool(2, &fastC_lay[1][hh], fracprod*doctofast[1]);
    }
    else
    {
        retention_pool(1, DOCpool, doctofast); 
        real1temp[0] = fracprod*doctofast[0];
        production_pool(1, &fastC_lay[0][hh], real1temp[0]);
    } 
    for(long k = 0; k < maxsoillayers; ++k)
        transfC[k] = 0.0;
    if(thickness_lay[2][hh] > 0.0)
    {
        transfC[2] = klo * tmpfcn[2] * smfcn[2] * fastC_lay[2][hh];
        retention_pool(maxsoillayers, fastC_lay, transfC, hh); 
        production_pool(maxsoillayers, &DOCpool[2], fracprod*transfC[2]);
    }
    else if(thickness_lay[1][hh] > 0.0)
    {
        transfC[1] = klo * tmpfcn[1] * smfcn[1] * fastC_lay[1][hh]; 
        retention_pool(2, fastC_lay, transfC, hh); 
        production_pool(2, &DOCpool[1], fracprod*transfC[1]);
    }
    else
    {
        transfC[0] = klo * tmpfcn[0] * smfcn[0] * fastC[0];
        retention_pool(1, fastC_lay, transfC, hh); 
        real1temp[0]=fracprod*transfC[0];
        production_pool(1, &DOCpool[0], real1temp[0]);
    } 
    for(long k = 0; k < maxsoillayers; ++k)
        transhC[k] = 0.0;
    if(thickness_lay[2][hh] > 0.0)
    {
        transhC[2] = kho * tmpfcn[2] * smfcn[2] * humusC_lay[2][hh];
        retention_pool(maxsoillayers, humusC_lay, transhC); 
        production_pool(maxsoillayers, &DOCpool[2], fracprod*transhC[2]);
    }
    else if(thickness_lay[1][hh] > 0.0)
    {
        transhC[1] = kho * tmpfcn[1] * smfcn[1] * humusC[1];
        retention_pool(2, humusC_lay, transhC); 
        production_pool(2, &DOCpool[1], fracprod*transhC[1]);
    }
    else
    {
        transhC[0] = kho * tmpfcn[0] * smfcn[0] * humusC_lay[0][hh];
        retention_pool(1, humusC_lay, transhC, hh);     
        real1temp[0] = fracprod*transhC[0];
        production_pool(1, &DOCpool[0], real1temp[0]);
    } 
    new_concentration(DOCpool[0], water_lay[0][hh], &conc_top_lay[i_oc][hh]);
    if(thickness_lay[1][hh] > 0.0)
        new_concentration(DOCpool[1], water_lay[1][hh], &conc_bottom_lay[i_oc][hh]);
    if(thickness_lay[2][hh] > 0.0)
        new_concentration(DOCpool[2], water_lay[2][hh], &conc_below_lay[i_oc][hh]);
freopen("c:\\injection.log", "a", stdout); printf("</voidClassWQ_Hype::soil_carbon_pool_transformations(constfloatcalcC,constfloat**wp_lay,constfloat**fc_lay,constfloat**pw_lay,float**thickness_lay,constfloatklh,constfloatklo,constfloatkho,constfloatkof,constfloatkoflim,constfloatminc,constfloatsoimf,constfloatsoimr) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
}
float ClassWQ_Hype::SUM(float X[][numsubstances], long Substance)
{
freopen("c:\\injection.log", "a", stdout); printf("<floatClassWQ_Hype::SUM(floatX[][numsubstances],longSubstance) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
    float sum = 0.0;
    for(long ii = 0; ii < maxsoillayers; ++ii)
        sum += X[ii][Substance];
{freopen("c:\\injection.log", "a", stdout); printf("</floatClassWQ_Hype::SUM(floatX[][numsubstances],longSubstance) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);return sum;}
freopen("c:\\injection.log", "a", stdout); printf("</floatClassWQ_Hype::SUM(floatX[][numsubstances],longSubstance) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
}
float ClassWQ_Hype::SUM(float *X)
{
freopen("c:\\injection.log", "a", stdout); printf("<floatClassWQ_Hype::SUM(float*X) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
    float sum = 0.0;
    for(long ii = 0; ii < maxsoillayers; ++ii)
        sum += X[ii];
{freopen("c:\\injection.log", "a", stdout); printf("</floatClassWQ_Hype::SUM(float*X) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);return sum;}
freopen("c:\\injection.log", "a", stdout); printf("</floatClassWQ_Hype::SUM(float*X) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
}
void ClassWQ_Hype::add_source_to_water(const float vol, const long n, float *conc, const float source)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassWQ_Hype::add_source_to_water(constfloatvol,constlongn,float*conc,constfloatsource) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
    if(vol > 0.0)
        *conc = (*conc*vol + source)/ vol;
freopen("c:\\injection.log", "a", stdout); printf("</voidClassWQ_Hype::add_source_to_water(constfloatvol,constlongn,float*conc,constfloatsource) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
}
void ClassWQ_Hype::add_source_to_water(const float vol, long n, float conc, float source)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassWQ_Hype::add_source_to_water(constfloatvol,longn,floatconc,floatsource) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
    if(vol > 0.0)
        conc = (conc*vol + source)/ vol;
freopen("c:\\injection.log", "a", stdout); printf("</voidClassWQ_Hype::add_source_to_water(constfloatvol,longn,floatconc,floatsource) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
}
float ClassWQ_Hype::tempfactor2(const float temp)
{
freopen("c:\\injection.log", "a", stdout); printf("<floatClassWQ_Hype::tempfactor2(constfloattemp) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
    float fcn;
    fcn = pow(2.0, (temp - 20.0) / 10.0);
    if(temp < 5.0)
        fcn = fcn * (temp / 5.0);
    if(temp < 0.0)
        fcn = 0.0;
{freopen("c:\\injection.log", "a", stdout); printf("</floatClassWQ_Hype::tempfactor2(constfloattemp) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);return fcn;}
freopen("c:\\injection.log", "a", stdout); printf("</floatClassWQ_Hype::tempfactor2(constfloattemp) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
}
float ClassWQ_Hype::exponential_moisturefactor(const float sm, const float pw, const float limpar, const float exp)
{
freopen("c:\\injection.log", "a", stdout); printf("<floatClassWQ_Hype::exponential_moisturefactor(constfloatsm,constfloatpw,constfloatlimpar,constfloatexp) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
    float smfcn;      
    smfcn = 0.0;
    if((sm/pw) > limpar)
    {
        smfcn = pow((((sm / pw)-limpar)/(1.0-limpar)), exp);
    }
{freopen("c:\\injection.log", "a", stdout); printf("</floatClassWQ_Hype::exponential_moisturefactor(constfloatsm,constfloatpw,constfloatlimpar,constfloatexp) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);return smfcn;}
freopen("c:\\injection.log", "a", stdout); printf("</floatClassWQ_Hype::exponential_moisturefactor(constfloatsm,constfloatpw,constfloatlimpar,constfloatexp) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
}
float ClassWQ_Hype::halfsatconcfactor(const float conc, const float par)
{
freopen("c:\\injection.log", "a", stdout); printf("<floatClassWQ_Hype::halfsatconcfactor(constfloatconc,constfloatpar) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
    float fcn;
    fcn = conc / (conc + par);
{freopen("c:\\injection.log", "a", stdout); printf("</floatClassWQ_Hype::halfsatconcfactor(constfloatconc,constfloatpar) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);return  fcn;}
freopen("c:\\injection.log", "a", stdout); printf("</floatClassWQ_Hype::halfsatconcfactor(constfloatconc,constfloatpar) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
}
void ClassWQ_Hype::retention_pool(long n, float **pool, float *sink, long CRHM_array)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassWQ_Hype::retention_pool(longn,float**pool,float*sink,longCRHM_array) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
    float a;
    for(long k = 0; k < n; ++k)
    {
        a = pool[k][hh] - sink[k];
        if(a >= 0.0)
            pool[k][hh] = a;
        else
        {
            sink[k] = pool[k][hh];
            pool[k][hh] = 0.0;
        }
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidClassWQ_Hype::retention_pool(longn,float**pool,float*sink,longCRHM_array) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
}
void ClassWQ_Hype::retention_pool(long n, float *pool, float *sink)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassWQ_Hype::retention_pool(longn,float*pool,float*sink) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
    float a;
    for(long k = 0; k < n; ++k)
    {
        a = pool[k] - sink[k];
        if(a >= 0.0)
            pool[k] = a;
        else
        {
            sink[k] = pool[k];
            pool[k] = 0.0;
        }
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidClassWQ_Hype::retention_pool(longn,float*pool,float*sink) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
}
void ClassWQ_Hype::production_pool(const long n, float **pool, const float *source, long CRHM_array)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassWQ_Hype::production_pool(constlongn,float**pool,constfloat*source,longCRHM_array) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
    for(long kk = 0; kk < n; ++kk)
        pool[kk][hh] = pool[kk][hh] + source[kk];
freopen("c:\\injection.log", "a", stdout); printf("</voidClassWQ_Hype::production_pool(constlongn,float**pool,constfloat*source,longCRHM_array) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
}
void ClassWQ_Hype::production_pool(const long n, float **pool, const float source[][numsubstances], long Application)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassWQ_Hype::production_pool(constlongn,float**pool,constfloatsource[][numsubstances],longApplication) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
    for(long kk = 0; kk < n; ++kk)
        pool[kk][hh] = pool[kk][hh] + source[kk][Application];
freopen("c:\\injection.log", "a", stdout); printf("</voidClassWQ_Hype::production_pool(constlongn,float**pool,constfloatsource[][numsubstances],longApplication) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
}
void ClassWQ_Hype::production_pool(const long n, float *pool, const float *source)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassWQ_Hype::production_pool(constlongn,float*pool,constfloat*source) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
    for(long kk = 0; kk < n; ++kk)
        pool[kk] = pool[kk] + source[kk];
freopen("c:\\injection.log", "a", stdout); printf("</voidClassWQ_Hype::production_pool(constlongn,float*pool,constfloat*source) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
}
void ClassWQ_Hype::production_pool(const long n, float *pool, float source)  
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassWQ_Hype::production_pool(constlongn,float*pool,floatsource) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
    *pool = *pool + source;
freopen("c:\\injection.log", "a", stdout); printf("</voidClassWQ_Hype::production_pool(constlongn,float*pool,floatsource) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
}
void ClassWQ_Hype::new_concentration(const float pool, const float vol, float *conc)  
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassWQ_Hype::new_concentration(constfloatpool,constfloatvol,float*conc) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
    if(vol > 0.0)
        *conc = pool / vol;
    else
        *conc = 0.0;
freopen("c:\\injection.log", "a", stdout); printf("</voidClassWQ_Hype::new_concentration(constfloatpool,constfloatvol,float*conc) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
}
void ClassWQ_Hype::new_concentration(const float pool, const float vol, float **conc)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassWQ_Hype::new_concentration(constfloatpool,constfloatvol,float**conc) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
    if(vol > 0.0)
        conc[i_in][hh] = pool / vol;
    else
        conc[i_in][hh] = 0.0;
freopen("c:\\injection.log", "a", stdout); printf("</voidClassWQ_Hype::new_concentration(constfloatpool,constfloatvol,float**conc) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
}
void ClassWQ_Hype::new_concentration(const float pool, float vol, float conc)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassWQ_Hype::new_concentration(constfloatpool,floatvol,floatconc) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
    if(vol > 0.0)
        conc = pool / vol;
    else
        conc = 0.0;
freopen("c:\\injection.log", "a", stdout); printf("</voidClassWQ_Hype::new_concentration(constfloatpool,floatvol,floatconc) @@@ Hype_routines.cpp_nocom>\n"); fclose(stdout);
}
