#include <vcl.h>
#pragma hdrstop
#include "Hype_lake.h"
#include "Hype_routines.h"
#include "Hype_routines.cpp"
#include "DefCRHMGlobal.h"
#include <math.h>
#pragma package(smart_init)
using namespace std;
using namespace CRHM;
ClassWQ_Lake* ClassWQ_Lake::klone(string name) const
{
freopen("c:\\injection.log", "a", stdout); printf("<ClassWQ_Lake*ClassWQ_Lake::klone(stringname)const @@@ Hype_lake.cpp_nocom>\n"); fclose(stdout);
{freopen("c:\\injection.log", "a", stdout); printf("</ClassWQ_Lake*ClassWQ_Lake::klone(stringname)const @@@ Hype_lake.cpp_nocom>\n"); fclose(stdout);return new ClassWQ_Lake(name);}
freopen("c:\\injection.log", "a", stdout); printf("</ClassWQ_Lake*ClassWQ_Lake::klone(stringname)const @@@ Hype_lake.cpp_nocom>\n"); fclose(stdout);
}
void ClassWQ_Lake::decl(void)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassWQ_Lake::decl(void) @@@ Hype_lake.cpp_nocom>\n"); fclose(stdout);
    Description = "'WQ Lake module.'";
    declstatvar("concslow", NHRU, "concentration of soil moisture per land-soil", "(mg/m^2)", &concslow, &concslow_lay, numsubstances);
    declvar("temp_l", NHRU, " (laketype,subbasin)", "(�C)", &temp_l);
    declvar("temp10_l", NHRU, "lake temperature10-day mean lake temperature (laketype,subbasin)", "(�C)", &temp10_l);
    declvar("temp20_l", NHRU, "20-day mean lake temperature (laketype,subbasin)", "(�C)", &temp20_l);
    declvar("TPmean_l", NHRU, "365-day mean Total Phosphorus concentration of lake (laketype,subbasin)", "(mg/m)", &TPmean_l);
    declstatvar("slowwater", NHRU, "volume or level of long turnover lake part (laketype,subbasin)", "(mm)", &slowwater);
    declparam("hru_area", NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);
    declparam("wp", NDEFN, "[1]", "1", "66", "water content at wilting point", "(mm)", &wp, &wp_lay, maxsoillayers);
    declparam("thickness", NDEFN, "[1]", "0", "100", "thickness of soil layers", "(mm)", &thickness, &thickness_lay, maxsoillayers);
    declparam("denpar", NHRU, "[1]", "0", "100", "parameter denitrification in soil", "(mm)", &denpar);
    declparam("calcN", NHRU, "[0]", "0", "1", "flag for nitrogen simulation", "()", &calcN);
    declparam("calcP", NHRU, "[0]", "0", "1", "flag for phosphorus simulation", "()", &calcP);
    declparam("conductP", NHRU, "[0]", "0", "1", "flag for conduct P", "()", &conductP);
    declparam("conductN", NHRU, "[0]", "0", "1", "flag for conduct P", "()", &conductN);
    declparam("cohesion", NHRU, "[100]", "0", "1000", "cohesion", "(kPa)", &cohesion);
    declparam("erodibility", NHRU, "[0]", "0", "1", "erodibility", "(g/J)", &erodibility);
    declparam("closewater", NHRU, "[0]", "0", "1", "part of area (possibly agricultural area) close to water courses", "()", &closewater);
    declparam("buffer", NHRU, "[0]", "0", "1", "part of river length with buffer zones (of river in the area above (e.g. agricultural area))", "()", &buffer);
    declparam("sedonpar", NHRU, "[0]", "0", "1", "flag for sedonpar ON sedimentation rate  (lakes)", "()", &sedonpar);
    declparam("sedpppar", NHRU, "[100]", "0", "1000", "PP sedimentation rate  (lakes)", "()", &sedpppar);
    declparam("limonpar", NHRU, "[100]", "0", "1000", "limitation of sedimentation parameter", "(mg/l)", &limonpar);
    declparam("limpppar", NHRU, "[100]", "0", "1000", "limitation of sedimentation parameter", "(mg/l)", &limpppar);
    declparam("prodNpar", NHRU, "[0]", "0", "1", "production rate ON in water", "()", &prodNpar);
    declparam("prodPpar", NHRU, "[100]", "0", "1000", "production rate PP in water", "()", &prodPpar);
    declparam("sedocpar", NHRU, "[100]", "0", "1000", "OC sedimentation rate  (lakes)", "(m/d)", &sedocpar);
    declparam("laketype", NHRU, "[1]", "1", "2", "Lake or river type (1=local, 2=main/outlet))", "()", &laketype); 
    declparam("lake_depth", NHRU, "[1]", "1", "10", "depth of lake", "(m)", &lake_depth);
    declparam("pppar", NHRU, "[1]", "1", "10", "internal load of particulate phosphorus", "()", &pppar);
    declparam("sppar", NHRU, "[1]", "1", "10", "internal load of soluble (reactive) phosphorus", "()", &sppar);
    declputvar("*", "conc_top", "(mg/m^2)", &conc_top, &conc_top_lay);
    declputvar("*", "conc_bottom", "(mg/m^2)", &conc_bottom, &conc_bottom_lay);
    declputvar("*", "conc_below", "(mg/m^2)", &conc_below, &conc_below_lay);
    declgetvar("*", "soil_moisture", "(mm)", &water);
    declgetvar("*", "hru_t", "(�C)", &hru_t);
    declgetvar("*", "SWE", "(mm)", &SWE);
    declgetvar("*", "net_rain", "(mm)", &net_rain);
    declgetvar("*", "runoff", "(mm)", &runoff);
    declgetvar("*", "soil_moist", "(mm)", &soil_moist);
    declgetvar("*", "SRP_conc", "(mg/l)", &SRP_conc);
    declgetvar("*", "poolPP", "(kg/km^2)", &poolPP);
    declgetparam("*", "soil_moist_max", "(mm)", &soil_moist_max);
freopen("c:\\injection.log", "a", stdout); printf("</voidClassWQ_Lake::decl(void) @@@ Hype_lake.cpp_nocom>\n"); fclose(stdout);
}
void ClassWQ_Lake::init(void)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassWQ_Lake::init(void) @@@ Hype_lake.cpp_nocom>\n"); fclose(stdout);
freopen("c:\\injection.log", "a", stdout); printf("</voidClassWQ_Lake::init(void) @@@ Hype_lake.cpp_nocom>\n"); fclose(stdout);
}
void ClassWQ_Lake::run(void)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassWQ_Lake::run(void) @@@ Hype_lake.cpp_nocom>\n"); fclose(stdout);
    if(nstep == 1 || Global::Freq == 1)  
    {
        for(hh = 0; chkStruct(); ++hh)
        {
            np_processes_in_lake(laketype[hh], hru_area[hh], denpar[hh], prodNpar[hh], prodPpar[hh], sedonpar[hh], sedpppar[hh], limonpar[hh], limpppar[hh]);
            oc_processes_in_lake(laketype[hh], hru_area[hh], prodPpar[hh], limpppar[hh], sedocpar[hh]);
        }
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidClassWQ_Lake::run(void) @@@ Hype_lake.cpp_nocom>\n"); fclose(stdout);
}
void ClassWQ_Lake::finish(bool good)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassWQ_Lake::finish(boolgood) @@@ Hype_lake.cpp_nocom>\n"); fclose(stdout);
    for(hh = 0; chkStruct(); ++hh)
    {
        LogMessage(hh, string("'" + Name + " (WQ_Hype)'").c_str(), BLANK);
    }
    LogDebug(" ");
freopen("c:\\injection.log", "a", stdout); printf("</voidClassWQ_Lake::finish(boolgood) @@@ Hype_lake.cpp_nocom>\n"); fclose(stdout);
}
void ClassWQ_Lake::np_processes_in_lake(const long laketype, const float area, const float denpar, const long prodNpar, const float prodPpar, const long sedonpar, const float sedpppar, const float limonpar, const float limpppar)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassWQ_Lake::np_processes_in_lake(constlonglaketype,constfloatarea,constfloatdenpar,constlongprodNpar,constfloatprodPpar,constlongsedonpar,constfloatsedpppar,constfloatlimonpar,constfloatlimpppar) @@@ Hype_lake.cpp_nocom>\n"); fclose(stdout);
    /*
        USE MODVAR, ONLY : conductN,conductP
        !Argument declarations
        long INTENT(IN) :: i          !<index of subbasin
        long, INTENT(IN) :: itype      !<lake type (ilake or olake)
        float, INTENT(IN)    :: area       !<lake area (m2)
        float, INTENT(IN)    :: denpar     !<model parameter denitrification rate (kg/m2/day)
        float, INTENT(IN)    :: prodNpar   !<model parameter production ON
        float, INTENT(IN)    :: prodPpar   !<model parameter production PP
        float, INTENT(IN)    :: sedonpar   !<ON sedimentation rate  (lakes)
        float, INTENT(IN)    :: sedpppar   !<PP sedimentation rate  (lakes)
        float, INTENT(IN)    :: limonpar   !<limitation of sedimentation parameter (mg/L)
        float, INTENT(IN)    :: limpppar   !<limitation of sedimentation parameter (mg/L)
        TYPE(lakestatetype),INTENT(INOUT) :: lakestate  !<Lake state
    */
    if(conductP[hh])
        calculate_lake_tpmean(laketype);
    if(conductN[hh])
        denitrification_water(laketype, area, denpar); 
    production_mineralisation(laketype, area, prodNpar, prodPpar, limpppar);  
    sedimentation_lake(laketype, area, sedonpar, sedpppar, limonpar, limpppar);  
    if(conductP[hh])
        internal_lake_load(laketype, area);  
freopen("c:\\injection.log", "a", stdout); printf("</voidClassWQ_Lake::np_processes_in_lake(constlonglaketype,constfloatarea,constfloatdenpar,constlongprodNpar,constfloatprodPpar,constlongsedonpar,constfloatsedpppar,constfloatlimonpar,constfloatlimpppar) @@@ Hype_lake.cpp_nocom>\n"); fclose(stdout);
}
void ClassWQ_Lake::calculate_lake_tpmean(const long laketype)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassWQ_Lake::calculate_lake_tpmean(constlonglaketype) @@@ Hype_lake.cpp_nocom>\n"); fclose(stdout);
    /*
        USE MODVAR, ONLY : i_sp,i_pp
        !Argument declarations
        long, INTENT(IN) :: i         !<index of current subbasin
        long, INTENT(IN) :: watertype !<Lake type (1=local, 2=outlet)
        TYPE(lakestatetype),INTENT(INOUT) :: lakestate  !<Lake state
    */
    float meanconc;
    meanconc = (water[hh]*(conc_top_lay[i_sp][hh] + conc_top_lay[i_pp][hh]) +
                slowwater[hh]*(concslow_lay[i_pp][hh] + concslow_lay[i_pp][hh]))/
               (water[hh] + slowwater[hh]);
    TPmean_l[hh] = TPmean_l[hh] + (meanconc - TPmean_l[hh])/365.0;
freopen("c:\\injection.log", "a", stdout); printf("</voidClassWQ_Lake::calculate_lake_tpmean(constlonglaketype) @@@ Hype_lake.cpp_nocom>\n"); fclose(stdout);
}
void ClassWQ_Lake::denitrification_water(const long laketype, const float area, const float denpar)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassWQ_Lake::denitrification_water(constlonglaketype,constfloatarea,constfloatdenpar) @@@ Hype_lake.cpp_nocom>\n"); fclose(stdout);
    /*
        USE MODVAR, ONLY : i_in
        USE HYPEVARIABLES, ONLY : halfsatINwater,   &
                                  maxdenitriwater
        !Argument declarations
        long, INTENT(IN) :: i          !<index of current subbasin
        long, INTENT(IN) :: watertype  !<Lake or river type (1=local, 2=main/outlet)
        long, INTENT(IN) :: systemtype !<aquatic system type (1=lake, 2=river)
        float, INTENT(IN)    :: area       !<lake surface area/river bottom area (m2)
        float, INTENT(IN)    :: denpar     !<model parameter denitrification rate (kg/m2/day)
        TYPE(riverstatetype),INTENT(INOUT),OPTIONAL :: riverstate  !<River states
        TYPE(lakestatetype),INTENT(INOUT),OPTIONAL  :: lakestate   !<Lake states
    */
    float denitri_water[1], inorganicNpool[1];
    float tmpfcn, concfcn, watertemp, waterconc, vol;
    const long pooldim = 1;
    vol = slowwater[hh] * hru_area[hh] * 1.0E-6;    
    waterconc = concslow_lay[i_in][hh];          
    inorganicNpool[0] = vol * waterconc;                          
    watertemp = temp_l[hh];
    tmpfcn  = tempfactor(watertemp);
    concfcn = halfsatconcfactor(waterconc, halfsatINwater);
    denitri_water[0] = denpar * area * concfcn * tmpfcn;   
    denitri_water[0] = min <float> (maxdenitriwater*inorganicNpool[0], denitri_water[0]);    
    retention_pool(pooldim, inorganicNpool, denitri_water);
    new_concentration(inorganicNpool[0], vol, concslow_lay[i_in][hh]);
freopen("c:\\injection.log", "a", stdout); printf("</voidClassWQ_Lake::denitrification_water(constlonglaketype,constfloatarea,constfloatdenpar) @@@ Hype_lake.cpp_nocom>\n"); fclose(stdout);
}
void ClassWQ_Lake::production_mineralisation(const long laketype, const float area, const float prodNpar, const float prodPpar, const float limpppar, const float depth)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassWQ_Lake::production_mineralisation(constlonglaketype,constfloatarea,constfloatprodNpar,constfloatprodPpar,constfloatlimpppar,constfloatdepth) @@@ Hype_lake.cpp_nocom>\n"); fclose(stdout);
    /*
        USE MODVAR, ONLY : conductN,conductP, &
                           i_in,i_on,i_sp,i_pp
        USE HYPEVARIABLES, ONLY : maxprodwater,   &
                                  maxdegradwater, &
                                  NPratio,        &
                                  halfsatTPwater
        !Argument declarations
        long, INTENT(IN) :: i          !<index of current subbasin
        long, INTENT(IN) :: watertype  !<Lake or river type (1=local, 2=main/outlet)
        long, INTENT(IN) :: systemtype !<aquatic system type (1=lake, 2=river)
        float, INTENT(IN)    :: area       !<lake surface area/ river bottom area (m2)
        float, INTENT(IN)    :: prodNpar   !<model parameter production rate ON in water
        float, INTENT(IN)    :: prodPpar   !<model parameter production rate PP in water
        float, INTENT(IN)    :: limpppar   !<limitation of sedimentation parameter (mg/L)
        TYPE(riverstatetype),INTENT(INOUT),OPTIONAL :: riverstate !<River states
        TYPE(lakestatetype),INTENT(INOUT),OPTIONAL  :: lakestate  !<Lake states
        float, INTENT(IN), OPTIONAL :: depth      !<river depth (m)
    */
    float ONpool[1], INpool[1], SRPpool[1], PPpool[1], minprodN[1], minprodP[1];
    float watertemp, waterTPmean, temp10, temp20;
    float tmpfcn, tmpfcn1, tmpfcn2, TPfcn;
    float vol;
    float waterdepth;     
    long pooldim = 1;
    if(!conductN[hh] && !conductP[hh])
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassWQ_Lake::production_mineralisation(constlonglaketype,constfloatarea,constfloatprodNpar,constfloatprodPpar,constfloatlimpppar,constfloatdepth) @@@ Hype_lake.cpp_nocom>\n"); fclose(stdout);return;}
    vol = slowwater[hh] * area / 1.0E6;
    if(conductN[hh])
    {
        INpool[0] = vol * concslow_lay[i_in][hh];   
        ONpool[0] = vol * concslow_lay[i_on][hh];   
    }
    if(conductP[hh])
    {
        SRPpool[0] = vol * concslow_lay[i_sp][hh];  
        PPpool[0]  = vol * concslow_lay[i_pp][hh];  
    }
    watertemp = temp_l[hh];
    waterdepth = slowwater[hh]/1000.;
    waterTPmean = TPmean_l[hh];
    if(watertemp > 0.0)  
    {
        TPfcn = halfsatconcfactor(max <float> (waterTPmean-limpppar,0.), halfsatTPwater);
        tmpfcn1 = watertemp / 20.0;
        tmpfcn2 = (temp10_l - temp20_l) / 5.0;
        tmpfcn = tmpfcn1*tmpfcn2;
        if(conductN[hh])
        {
            minprodN[0] = prodNpar * TPfcn * tmpfcn * waterdepth * area;  
            if(minprodN[hh] > 0.0)   
                minprodN[0] = min <float> (maxprodwater * INpool[0], minprodN[0]);
            else                       
                minprodN[0] = max <float>(-maxdegradwater * ONpool[0], minprodN[0]);
            retention_pool(pooldim, INpool, minprodN);   
            production_pool(pooldim, ONpool, minprodN);
        }
        if(conductP[hh])
        {
            minprodP[0] = prodPpar * NPratio * TPfcn * tmpfcn * waterdepth * area;  
            if(minprodP[0] > 0.0)   
                minprodP[0] = min <float>(maxprodwater * SRPpool[0], minprodP[0]);
            else                       
                minprodP[0] = max <float>(-maxdegradwater * PPpool[0], minprodP[0]);
            retention_pool(pooldim, SRPpool, minprodP);    
            production_pool(pooldim, PPpool, minprodP);
        }
        if(conductN[hh])
            new_concentration(INpool[0], vol, concslow_lay[i_in][hh]);
        if(conductN[hh])
            new_concentration(ONpool[0], vol, concslow_lay[i_on][hh]);
        if(conductP[hh])
            new_concentration(SRPpool[0], vol, concslow_lay[i_sp][hh]);
        if(conductP[hh])
            new_concentration(PPpool[0], vol, concslow_lay[i_pp][hh]);
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidClassWQ_Lake::production_mineralisation(constlonglaketype,constfloatarea,constfloatprodNpar,constfloatprodPpar,constfloatlimpppar,constfloatdepth) @@@ Hype_lake.cpp_nocom>\n"); fclose(stdout);
}
void ClassWQ_Lake::sedimentation_lake(const long laketype, const float area, const float sedonpar, const float sedpppar, const float limonpar, const float limpppar)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassWQ_Lake::sedimentation_lake(constlonglaketype,constfloatarea,constfloatsedonpar,constfloatsedpppar,constfloatlimonpar,constfloatlimpppar) @@@ Hype_lake.cpp_nocom>\n"); fclose(stdout);
    /*
        USE MODVAR, ONLY : conductN,conductP, &
                           i_on,i_pp
        !Argument declarations
        long, INTENT(IN) :: i          !<index of current subbasin
        long, INTENT(IN) :: watertype  !<Lake type (1=local, 2=outlet)
        float, INTENT(IN)    :: area       !<lake surface area (m2)
        float, INTENT(IN)    :: sedonpar   !<ON sedimentation rate  (lakes) (m/d)
        float, INTENT(IN)    :: sedpppar   !<PP sedimentation rate  (lakes) (m/d)
        float, INTENT(IN)    :: limonpar   !<limitation of sedimentation parameter (mg/L)
        float, INTENT(IN)    :: limpppar   !<limitation of sedimentation parameter (mg/L)
        TYPE(lakestatetype),INTENT(INOUT) :: lakestate  !<Lake state
    */
    float waterconcON, waterconcPP;
    float ONpool[1], PPpool[1]; 
    float sedON[1], sedPP[1];   
    float vol;
    if(!conductN[hh] && !conductP[hh])
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassWQ_Lake::sedimentation_lake(constlonglaketype,constfloatarea,constfloatsedonpar,constfloatsedpppar,constfloatlimonpar,constfloatlimpppar) @@@ Hype_lake.cpp_nocom>\n"); fclose(stdout);return;}
    vol = slowwater[hh] * area * 1.0E-6;
    if(conductN[hh])
    {
        ONpool[0] = vol * concslow_lay[i_on][hh];  
        waterconcON = concslow_lay[i_on][hh]; 
    }
    if(conductP[hh])
    {
        PPpool[0] = vol * concslow_lay[i_pp][hh];  
        waterconcPP = concslow_lay[i_pp][hh]; 
    }
    if(conductN[hh])
        sedON[0] = sedonpar * max <float>(waterconcON-limonpar, 0.0) * 1.0E-3 * area;    
    if(conductP[hh])
        sedPP[0] = sedpppar * max <float>(waterconcPP-limpppar, 0.0) * 1.0E-3 * area;    
    if(conductN[hh])
        retention_pool(1, ONpool, sedON);
    if(conductP[hh])
        retention_pool(1, PPpool, sedPP);
    if(conductN[hh])
        new_concentration(ONpool[0], vol, concslow_lay[i_on][hh]);
    if(conductP[hh])
        new_concentration(PPpool[0], vol, concslow_lay[i_pp][hh]);
freopen("c:\\injection.log", "a", stdout); printf("</voidClassWQ_Lake::sedimentation_lake(constlonglaketype,constfloatarea,constfloatsedonpar,constfloatsedpppar,constfloatlimonpar,constfloatlimpppar) @@@ Hype_lake.cpp_nocom>\n"); fclose(stdout);
}
void ClassWQ_Lake::internal_lake_load(const long laketype, const float area)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassWQ_Lake::internal_lake_load(constlonglaketype,constfloatarea) @@@ Hype_lake.cpp_nocom>\n"); fclose(stdout);
    /*
        USE MODVAR, ONLY : lakeindex,   &
                           lakedatapar, &
                           lakedataparindex,  &
                           i_sp,i_pp,   &
                           numsubstances
        USE HYPEVARIABLES, ONLY : m_ldprodpp,  &
                                  m_ldprodsp
        !Argument declarations
        long, INTENT(IN) :: i           !<index of current subbasin
        long, INTENT(IN) :: watertype   !<Lake or river type (1=local, 2=main/outlet)
        long, INTENT(IN) :: systemtype  !<aquatic system type (1=lake, 2=river)
        float, INTENT(IN)    :: area        !<lake surface area/ river bottom area (m2)
        TYPE(lakestatetype),INTENT(INOUT) :: lakestate  !<Lake state
    */
    float prodPP, prodSP;
    float tmpfcn, TPfcn;
    float vol;
    float sourceP[numsubstances];
    if(laketype == 1)
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassWQ_Lake::internal_lake_load(constlonglaketype,constfloatarea) @@@ Hype_lake.cpp_nocom>\n"); fclose(stdout);return;}
    if(pppar == 0 && sppar == 0)
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassWQ_Lake::internal_lake_load(constlonglaketype,constfloatarea) @@@ Hype_lake.cpp_nocom>\n"); fclose(stdout);return;}
    sourceP[0] = 0.0;
    TPfcn = 0.1;
    tmpfcn = pow(0.86, (abs(temp_l[hh]) -15.));   
    prodPP = pppar[hh] * TPfcn * tmpfcn * area / 1000.0;  
    prodSP = sppar[hh] * TPfcn * tmpfcn * area / 1000.0;  
    sourceP[i_pp] = prodPP;
    sourceP[i_sp] = prodSP;
    vol = slowwater[hh] * area / 1.0E6;
    add_source_to_water(vol, numsubstances, concslow_lay[i_in][hh], sourceP[hh]);
freopen("c:\\injection.log", "a", stdout); printf("</voidClassWQ_Lake::internal_lake_load(constlonglaketype,constfloatarea) @@@ Hype_lake.cpp_nocom>\n"); fclose(stdout);
}
void ClassWQ_Lake::oc_processes_in_lake(const long watertype, const long area, const long prodpar, const long limpppar, const long sedocpar)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassWQ_Lake::oc_processes_in_lake(constlongwatertype,constlongarea,constlongprodpar,constlonglimpppar,constlongsedocpar) @@@ Hype_lake.cpp_nocom>\n"); fclose(stdout);
    /*
        !Argument declarations
        INTEGER, INTENT(IN) :: i                        !<current index of subbasin
        INTEGER, INTENT(IN) :: watertype                !<lake type (ilake or olake)
        REAL, INTENT(IN)    :: area                     !<lake area (m2)
        REAL, INTENT(IN)    :: prodpar                  !<model parameter production OC
        REAL, INTENT(IN)    :: limpppar                 !<limitation of sedimentation parameter (mg/L)
        REAL, INTENT(IN)    :: sedocpar                 !<OC sedimentation rate  (lakes)
        TYPE(lakestatetype),INTENT(INOUT) :: lakestate  !<Lake state
    */
    oc_production_mineralisation(area, prodpar, limpppar,
                                 slowwater[hh], concslow_lay[i_oc][hh],
                                 temp[hh], TPmean_l[hh], temp10_l[hh], temp20_l[hh], lake_depth[hh]);
    oc_sedimentation(area, sedocpar); 
freopen("c:\\injection.log", "a", stdout); printf("</voidClassWQ_Lake::oc_processes_in_lake(constlongwatertype,constlongarea,constlongprodpar,constlonglimpppar,constlongsedocpar) @@@ Hype_lake.cpp_nocom>\n"); fclose(stdout);
}
void ClassWQ_Lake::oc_production_mineralisation(const float area, float prodpar, float limpppar, float water, float conc, float watertemp, float waterTPmean, float temp10, float temp20, float depth)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassWQ_Lake::oc_production_mineralisation(constfloatarea,floatprodpar,floatlimpppar,floatwater,floatconc,floatwatertemp,floatwaterTPmean,floattemp10,floattemp20,floatdepth) @@@ Hype_lake.cpp_nocom>\n"); fclose(stdout);
    /*
        USE HYPEVARIABLES, ONLY : halfsatTPwater, &
                                  maxdegradwater, &
                                  NCratio
        !Argument declarations
        long, INTENT(IN)        :: systemtype  !<aquatic system type (1=lake, 2=river)
        float, INTENT(IN)           :: area        !<lake surface area/ river bottom area (m2)
        float, INTENT(IN)           :: prodpar     !<model parameter production rate OC in water
        float, INTENT(IN)           :: limpppar    !<limitation of sedimentation parameter (mg/L)
        float, INTENT(IN)           :: water       !<river or lake water (mm or m3)
        float, INTENT(INOUT)        :: conc        !<OC concentration of river or lake
        float, INTENT(IN)           :: watertemp   !<water temperature
        float, INTENT(IN)           :: waterTPmean !<water TP mean
        float, INTENT(IN)           :: temp10      !<10-day water temperature
        float, INTENT(IN)           :: temp20      !<20-day water temperature
        float, INTENT(IN), OPTIONAL :: depth       !<river depth (m)
    */
    float OCpool[1], minprodN[1], minprodC[1], minC[1], prodC[1];
    float tmpfcn, tmpfcn1, tmpfcn2, TPfcn;
    float vol;
    float waterdepth; 
    const long pooldim = 1;
    OCpool[1] = (water * area * conc)/ 1.0E6; 
    waterdepth = depth/1000.0;
    TPfcn = halfsatconcfactor(waterTPmean - limpppar, halfsatTPwater);
    if(watertemp >= 0.0)
        tmpfcn1 = watertemp / 20.0;
    else
        tmpfcn1 = 0.0;
    tmpfcn2 = (temp10 - temp20) / 5.0;
    tmpfcn = tmpfcn1*tmpfcn2;
    minprodN[0] = 0.0;
    if(watertemp > 0.0)
    {
        minprodN[0] = prodpar * TPfcn * tmpfcn * waterdepth * area;  
        if(minprodN[0] > 0.0)  
            minprodC[0] = minprodN[0] * NCratio;
        else                       
            minprodC[0] = max <float>(-maxdegradwater * OCpool[0], minprodN[0] * NCratio);
    }
    minC[0] = -minprodC[0];
    prodC[0] = minprodC[0];
    if(minprodC[0] > 0.0)
        production_pool(pooldim, OCpool, prodC);
    if(minprodC[0] < 0.0)
        retention_pool(pooldim, OCpool, minC);
    if(water > 0.0)   
    {
        vol = water * area/1.0E6;
        new_concentration(OCpool[0], vol, conc);
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidClassWQ_Lake::oc_production_mineralisation(constfloatarea,floatprodpar,floatlimpppar,floatwater,floatconc,floatwatertemp,floatwaterTPmean,floattemp10,floattemp20,floatdepth) @@@ Hype_lake.cpp_nocom>\n"); fclose(stdout);
}
void ClassWQ_Lake::oc_sedimentation(const float area, const float sedocpar)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassWQ_Lake::oc_sedimentation(constfloatarea,constfloatsedocpar) @@@ Hype_lake.cpp_nocom>\n"); fclose(stdout);
    /*
        USE MODVAR, ONLY : i_oc
        !Argument declarations
        INTEGER, INTENT(IN) :: i          !<current index of subbasin
        INTEGER, INTENT(IN) :: watertype  !<Lake or river type (1=local, 2=main/outlet)
        REAL, INTENT(IN)    :: area       !<lake surface area (m2)
        REAL, INTENT(IN)    :: sedocpar   !<OC sedimentation rate  (lakes) (m/d)
        TYPE(lakestatetype),INTENT(INOUT) :: lakestate  !<Lake state
    */
    float OCpool;          
    float sedOC ;          
    float vol;
    OCpool = (slowwater[hh] * concslow_lay[i_oc][hh] * area) / 1.0E6; 
    sedOC = (sedocpar * (concslow_lay[i_oc][hh]) / 1000.0) * area;    
    retention_pool(1, &OCpool, &sedOC);
    vol = slowwater[hh] * area / 1.0E6;
    new_concentration(OCpool, vol, concslow_lay[i_oc][hh]);
freopen("c:\\injection.log", "a", stdout); printf("</voidClassWQ_Lake::oc_sedimentation(constfloatarea,constfloatsedocpar) @@@ Hype_lake.cpp_nocom>\n"); fclose(stdout);
}
