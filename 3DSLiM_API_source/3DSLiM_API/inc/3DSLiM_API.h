/**
  ******************************************************************************
  * @file    3DSLiM_API.h
  * @author  SDK Team
  * @version V1.0.0
  * @date    30-January-2019
  * @brief   Header of 3DSLiM_API.cpp
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2018 Opus Microsystems </center></h2>
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _3DSLiM_API_H
#define _3DSLiM_API_H

#ifdef _3DSLIM_API_EXPORT
#define _3DSLIM_API_FUNC   __declspec(dllexport)
#else
#define _3DSLIM_API_FUNC
#endif

/* Includes ------------------------------------------------------------------*/
#ifdef _WIN64
#include <Windows.h>
#endif

#include <iostream>
#include "OpUSBDev.h"
#include "3DSLiM_types.h"
using namespace std;

/* Class definition and exported functions -----------------------------------*/
class _3DSLIM_API_FUNC _3DSLiM_API : public OpUSBDev
{
	public:
		_3DSLiM_API(void);
		~_3DSLiM_API(void);

		virtual return_status initialize(int dev_num);
		return_status config_parameter(_3DSLiM_parameter* parameter);
		return_status config_parameter(_3DSLiM_parameter_type type, void* value);
		return_status start(_3DSLiM_data_type type, _3DSLiM_xfer_mode mode, int rgb_cam_dev_num = 0); // start streaming data or getting one shot data
		return_status stop(void); // stop streaming data or getting one shot data
		return_status get_stream_data(_3DSLiM_output_data** data); // get point cloud or ir image
		return_status release_stream_data(_3DSLiM_output_data* data); // return output data object
		return_status init_one_shot_buffer(_3DSLiM_output_data** data);
		return_status get_one_shot_data(_3DSLiM_output_data* data);
		return_status delete_one_shot_buffer(_3DSLiM_output_data* data);
		return_status config_exposure(Exposure_mode exp_mode, int value = 1); // set auto/manual exposure
		return_status config_resolution(_3DSLiM_resolution resolution);
		_3DSLiM_resolution get_resolution(void);
		return_status save_ply_file(_3DSLiM_output_data* data, string filename);
		string read_lib_version(void);
		void* get_ctrl();

		friend class Eng_API;

	private:
		void* ctrl;
};

#endif // _3DSLiM_API

/************************ (C) COPYRIGHT Opus Microsystems *****END OF FILE****/
