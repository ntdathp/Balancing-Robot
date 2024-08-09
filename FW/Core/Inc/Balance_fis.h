/* Fuzzy inference system generated by qfiscgen.m for the qFIS engine*/
/* Generated : 29-Apr-2023 08:40:28 */
/* MATLAB Version: 9.11.0.1769968 (R2021b) */
/* Note: Based on the qFIS engine from https://github.com/kmilo17pet/qlibs */

#ifndef BALANCE_FIS_H
#define BALANCE_FIS_H

#ifdef __cplusplus
    extern "C" {
#endif

    void Balance_init( void );
    void Balance_run( float *inputs, float *outputs );

#ifdef __cplusplus
    }
#endif

#endif /* BALANCE_FIS_H */