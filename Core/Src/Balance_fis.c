/* Fuzzy inference system generated by qfiscgen.m for the qFIS engine*/
/* Generated : 29-Apr-2023 08:40:28 */
/* MATLAB Version: 9.11.0.1769968 (R2021b) */
/* Note: Based on the qFIS engine from https://github.com/kmilo17pet/qlibs */

#include "Balance_fis.h"
#include "qfis.h"

/* FIS Object */
static qFIS_t Balance;
/* I/O Fuzzy Objects */
static qFIS_Input_t Balance_inputs[ 2 ];
static qFIS_Output_t Balance_outputs[ 1 ];
/* I/O Membership Objects */
static qFIS_MF_t MFin[ 10 ], MFout[ 7 ];
/* I/O Names */
enum { e, edot };
enum { u };
/* I/O Membership functions tags */
enum { e_NB, e_ZE, e_PB, e_NS, e_PS, edot_NB, edot_ZE, edot_PB, edot_NS, edot_PS };
enum { u_NB, u_NM, u_NS, u_ZE, u_PS, u_PM, u_PB };
/* Rules of the inference system */
static const qFIS_Rules_t rules[] = { 
    QFIS_RULES_BEGIN
       IF e IS e_NB AND edot IS edot_NB THEN u IS u_NB END
       IF e IS e_NB AND edot IS edot_NS THEN u IS u_NB END
       IF e IS e_NB AND edot IS edot_ZE THEN u IS u_NM END
       IF e IS e_NB AND edot IS edot_PS THEN u IS u_NS END
       IF e IS e_NB AND edot IS edot_PB THEN u IS u_ZE END
       IF e IS e_NS AND edot IS edot_NB THEN u IS u_NB END
       IF e IS e_NS AND edot IS edot_NS THEN u IS u_NM END
       IF e IS e_NS AND edot IS edot_ZE THEN u IS u_NS END
       IF e IS e_NS AND edot IS edot_PS THEN u IS u_ZE END
       IF e IS e_NS AND edot IS edot_PB THEN u IS u_PS END
       IF e IS e_ZE AND edot IS edot_NB THEN u IS u_NM END
       IF e IS e_ZE AND edot IS edot_NS THEN u IS u_NS END
       IF e IS e_ZE AND edot IS edot_ZE THEN u IS u_ZE END
       IF e IS e_ZE AND edot IS edot_PS THEN u IS u_PS END
       IF e IS e_ZE AND edot IS edot_PB THEN u IS u_PM END
       IF e IS e_PS AND edot IS edot_NB THEN u IS u_NS END
       IF e IS e_PS AND edot IS edot_NS THEN u IS u_ZE END
       IF e IS e_PS AND edot IS edot_ZE THEN u IS u_PS END
       IF e IS e_PS AND edot IS edot_PS THEN u IS u_PM END
       IF e IS e_PS AND edot IS edot_PB THEN u IS u_PB END
       IF e IS e_PB AND edot IS edot_NB THEN u IS u_ZE END
       IF e IS e_PB AND edot IS edot_NS THEN u IS u_PS END
       IF e IS e_PB AND edot IS edot_ZE THEN u IS u_PM END
       IF e IS e_PB AND edot IS edot_PS THEN u IS u_PB END
       IF e IS e_PB AND edot IS edot_PB THEN u IS u_PB END
    QFIS_RULES_END
};
/* Rule strengths */
float rStrength[ 25 ] = { 0.0f };

/* Parameters of the membership functions */
static const float e_NB_p[] = { -1.7500f, -1.0830f, -0.3500f, -0.2500f };
static const float e_ZE_p[] = { -0.1500f, -0.0500f, 0.0500f, 0.1500f };
static const float e_PB_p[] = { 0.2500f, 0.3500f, 1.0800f, 1.7500f };
static const float e_NS_p[] = { -0.3500f, -0.2500f, -0.1500f, -0.050f };
static const float e_PS_p[] = { 0.0500f, 0.1500f, 0.2500f, 0.35000f };
static const float edot_NB_p[] = { -10.0000f, -1.0000f, -0.2500f };
static const float edot_ZE_p[] = { -0.2500f, -0.0500f, 0.0500f, 0.2500f };
static const float edot_PB_p[] = { 0.2500f, 1.0000f, 10.0000f };
static const float edot_NS_p[] = { -0.6000f, -0.2500f, 0.0500f };
static const float edot_PS_p[] = { 0.0500f, 0.2500f, 0.6000f };
static const float u_NB_p[] = { -1.0000f };
static const float u_NM_p[] = { -0.7500f };
static const float u_NS_p[] = { -0.4500f };
static const float u_ZE_p[] = { 0.0000f };
static const float u_PS_p[] = { 0.4500f };
static const float u_PM_p[] = { 0.7500f };
static const float u_PB_p[] = { 1.0000f };

void Balance_init( void ){
    /* Set inputs */
    qFIS_InputSetup( Balance_inputs, e, -1.0000f, 1.0000f );
    qFIS_InputSetup( Balance_inputs, edot, -1.0000f, 1.0000f );
    /* Set outputs */
    qFIS_OutputSetup( Balance_outputs, u, -1.0000f, 1.0000f );
    /* Set membership functions for the inputs */
    qFIS_SetMF( MFin, e, e_NB, trapmf, NULL, e_NB_p, 1.0f );
    qFIS_SetMF( MFin, e, e_ZE, trapmf, NULL, e_ZE_p, 1.0f );
    qFIS_SetMF( MFin, e, e_PB, trapmf, NULL, e_PB_p, 1.0f );
    qFIS_SetMF( MFin, e, e_NS, trapmf, NULL, e_NS_p, 1.0f );
    qFIS_SetMF( MFin, e, e_PS, trapmf, NULL, e_PS_p, 1.0f );
    qFIS_SetMF( MFin, edot, edot_NB, trimf, NULL, edot_NB_p, 1.0f );
    qFIS_SetMF( MFin, edot, edot_ZE, trapmf, NULL, edot_ZE_p, 1.0f );
    qFIS_SetMF( MFin, edot, edot_PB, trimf, NULL, edot_PB_p, 1.0f );
    qFIS_SetMF( MFin, edot, edot_NS, trimf, NULL, edot_NS_p, 1.0f );
    qFIS_SetMF( MFin, edot, edot_PS, trimf, NULL, edot_PS_p, 1.0f );
    /* Set membership functions for the outputs */
    qFIS_SetMF( MFout, u, u_NB, constantmf, NULL, u_NB_p, 1.0f );
    qFIS_SetMF( MFout, u, u_NM, constantmf, NULL, u_NM_p, 1.0f );
    qFIS_SetMF( MFout, u, u_NS, constantmf, NULL, u_NS_p, 1.0f );
    qFIS_SetMF( MFout, u, u_ZE, constantmf, NULL, u_ZE_p, 1.0f );
    qFIS_SetMF( MFout, u, u_PS, constantmf, NULL, u_PS_p, 1.0f );
    qFIS_SetMF( MFout, u, u_PM, constantmf, NULL, u_PM_p, 1.0f );
    qFIS_SetMF( MFout, u, u_PB, constantmf, NULL, u_PB_p, 1.0f );

    /* Configure the Inference System */
    qFIS_Setup( &Balance, Sugeno,
                Balance_inputs, sizeof(Balance_inputs),
                Balance_outputs, sizeof(Balance_outputs),
                MFin, sizeof(MFin), MFout, sizeof(MFout),
                rules, rStrength, 25u );
    qFIS_SetDeFuzzMethod( &Balance, wtsum );
    qFIS_SetParameter( &Balance, qFIS_AND, qFIS_PROD );
    qFIS_SetParameter( &Balance, qFIS_OR, qFIS_PROBOR );
    qFIS_SetParameter( &Balance, qFIS_Implication, qFIS_PROD );
    qFIS_SetParameter( &Balance, qFIS_Aggregation, qFIS_SUM );
}

void Balance_run( float *inputs, float *outputs ) {
    /* Set the crips inputs */
    qFIS_SetInput( Balance_inputs, e, inputs[ e ] );
    qFIS_SetInput( Balance_inputs, edot, inputs[ edot ] );

    qFIS_Fuzzify( &Balance );
    if ( qFIS_Inference( &Balance ) > 0 ) {
        qFIS_DeFuzzify( &Balance );
    }
    else {
        /* Error! */
    }

    /* Get the crips outputs */
    outputs[ u ] = qFIS_GetOutput( Balance_outputs, u );
}
