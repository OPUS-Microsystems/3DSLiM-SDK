/**
  ******************************************************************************
  * @file    3DSLiM_types.h
  * @author  SDK Team
  * @version V1.0.0
  * @date    24-December-2019
  * @brief   3DSLiM common types
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2019 Opus Microsystems </center></h2>
  ******************************************************************************
  */

#ifndef _3DSLIM_TYPES_H
#define _3DSLIM_TYPES_H

/* Exported macro ------------------------------------------------------------*/
/* Enumeration for resolution */
typedef enum _3DSLiM_resolution
{
	RESOLUTION_1280_720 = 0,
	RESOLUTION_1280_800,
	RESOLUTION_640_400
}_3DSLiM_resolution;

typedef enum _3DSLiM_data_type
{
	PCD_XYZ = 0,
	PCD_XYZ_RGB,
	IR_IMG
}_3DSLiM_data_type;

typedef enum _3DSLiM_xfer_mode
{
	ONE_SHOT = 0,
	STREAMING
}_3DSLiM_xfer_mode;

typedef enum Exposure_mode
{
	MANUAL = 0,
	AUTO
}Exposure_mode;

typedef enum _3DSLiM_parameter_type
{
	MIN_Z_CUTOFF = 0,
	MAX_Z_CUTOFF,
	SENSITIVITY, // value range = (0~1)
	NOISE_FILTERING_FACTOR, // value range = (0.0~1.0)
	POINT_CLOUD_SMOOTHING, // smoothing on/off switch
	POINT_CLOUD_SMOOTHING_KERNEL_SIZE, // value range = (3~9)
	MOTION_NOISE_FILTERING, // motion noise filtering on/off switch
	MOTION_NOISE_FILTERING_FACTOR, // value range = (0.01~0.20)
	RESAMPLING, // resampling on/off switch
	RESAMPLING_FACTOR, // value range = (0.05~1.0)
	QUALITY_FACTOR 
}_3DSLiM_parameter_type;

typedef struct img_pcd_data
{
	unsigned char* img_data;
	unsigned short* depth_map; // 16bits depth map
	float* pcd_data;
	unsigned char* mapped_rgb; // NULL if _3DSLiM_data_type == PCD_XYZ
}img_pcd_data;

typedef struct _3DSLiM_output_data
{
	int total_num; // number of points
	int effective_num; // effect number of points
	void* data;  // could be point cloud or raw pixel values
}_3DSLiM_output_data;

typedef struct _3DSLiM_parameter
{
	int quality_factor; // integer, 1 ~ 9, default value =7. Quality_factor cannot be change on fly.
	
	int min_z_cutoff; // 0~2000
	int max_z_cutoff; // 0~2000

	unsigned char f_point_cloud_smoothing; // bool flag
	int point_cloud_smoothing_k_size; // 

	float sensitivity; // 0~1, floating, higher value is more sensitive
	float noise_filtering_factor; // 0(min)~1(max), 1 has strongest effect of noise filtering.
	
	bool f_motion_noise_filtering;
	float threshold_motion_noise_factor;

	bool f_resampling;
	float resampling_factor; 

}_3DSLiM_parameter;

#endif // _3DSLIM_TYPES_H

/************************ (C) COPYRIGHT Opus Microsystems *****END OF FILE****/
