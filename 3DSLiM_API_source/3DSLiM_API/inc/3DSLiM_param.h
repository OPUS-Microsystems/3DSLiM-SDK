/**
  ******************************************************************************
  * @file    3DSLiM_param.h
  * @author  SDK Team
  * @version V1.0.0
  * @date    24-December-2019
  * @brief   3DSLiM parameter macros
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2019 Opus Microsystems </center></h2>
  ******************************************************************************
  */

#ifndef _3DSLIM_PARAM_H
#define _3DSLIM_PARAM_H

/* Exported macro ------------------------------------------------------------*/

/* Quality factor:
. Setting a higher value to reduce the noise caused by white noise, but will make sensor more sensitive to the sensing range.
and may reduce the sensing range.
. Integer, value range = (3, 9), default = 7;
. 'NOT' support execution time value change.
*/
#define _3DSLIM_DEFAULT_PAR_QUALITY_FACTOR (7)

/* z_cutoff :  Control the sensing range (mini-meter) .
. Integer,  value range = (0, 2000)mm,  min_z_cutoff default = 30, max_z_cutoff default = 1200;
. this parameters control the mapping range of dapth map p_depth: min_z_cutoff --> max_z_cutoff  to  65535 -->0.
. Support execution time value change.
*/
#define _3DSLIM_DEFAULT_PAR_MIN_Z_CUTOFF (30)
#define _3DSLIM_DEFAULT_PAR_MAX_Z_CUTOFF (1200)

/* sensitivity: Control 3D sensing sensitivity.
. Setting a higher value makes the sensor more sensitive to the 3D information of object with low reflection.
. Float, value range = (0, 1.0), default = 0.90.
. Support execution time value change.
*/
#define _3DSLIM_DEFAULT_PAR_SENSITIVITY (0.90)


/* noise_filtering_factor: remove noise points.
. Float, value range = (0, 1.0), default = 0.15.
. Value 0 means turn off noise filtering.
. Support execution time value change.
*/
#define _3DSLIM_DEFAULT_PAR_NOISE_FILTERING_FACTOR (0.15)

/* point_cloud_smoothing_k_size:
. Odd integer, value = (3, 5, 7, 9), default = 5.
. Support execution time value change.
*/
#define _3DSLIM_DEFAULT_PAR_F_POINT_CLOUD_SMOOTHING (true)
#define _3DSLIM_DEFAULT_PAR_POINT_CLOUD_SMOOTHING_FACTOR (5)


/*Experimental feature */
/* resampling_factor:
. Setting a higher value will reduce the desnity of point cloud.
. Float, value range = (0.001, 1.0), default = 0.0025
. Support execution time value change.
*/
#define _3DSLIM_DEFAULT_PAR_F_RESAMPLING (false)
#define _3DSLIM_DEFAULT_PAR_RESAMPLING_FACTOR (0.0025)

/*Experimental feature */
/* threshold_motion_noise_factor:
. Smaller value will make sensor more sensitive to the motion noise.
. Float, value range = (0.05, 0.20), default = 0.08.
. Support execution time value change.
*/
#define _3DSLIM_DEFAULT_PAR_F_MOTION_NOISE_FILTERING (false)
#define _3DSLIM_DEFAULT_PAR_MOTION_NOISE_FILTERING_FACTOR (0.08)


#endif // _3DSLIM_PARAM_H

/************************ (C) COPYRIGHT Opus Microsystems *****END OF FILE****/
