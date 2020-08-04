#include <iostream>
#include <vector>
#include <fstream>
#include <opencv2/opencv.hpp>
#include "3DSLiM_types.h"
#include "3DSLiM_API.h"
#include "3DSLiM_param.h"

using namespace std;
using namespace cv;

/* Main control flow demo function */
int test_get_data(const _3DSLiM_xfer_mode xfer_mode, const _3DSLiM_resolution  RES);

// sub functions.
void config_parameters(_3DSLiM_parameter* p_param); /* example of how to config parameters */
void use_output_data_example(_3DSLiM_API* _3DCam, const _3DSLiM_xfer_mode  xfer_mode, _3DSLiM_output_data* output); /* example of how to use data*/

int waitKey_val = 0;
int Width = 0, Height = 0;
int num_of_pcd = 50;

int main()
{
	/*
	test_get_data is a control flow demo function.
	>> get 16 bits depth map from ((img_pcd_data*)_3DSLiM_output_data->data)->depth_map (mapping range is controlled by _3DSLiM_parameter->min_z_cutoff and max_z_cutoff )
	>> get point-cloud floating data xyz from ((img_pcd_data*)_3DSLiM_output_data->data)->pcd_data
	*/
	test_get_data(STREAMING, RESOLUTION_640_400);
	//test_get_data(ONE_SHOT, RESOLUTION_640_400);

	/* NOTICE */
	/* If your 3D camera module is mounted with an extra IR camera and connected with another
	USB cable, note that we do not provide sample code for accessing that IR camera. We suggest
	that you use 3rd party library (ex. OpenCV) to access it. */

	return 0;
}


// Get data example.
int test_get_data(const _3DSLiM_xfer_mode xfer_mode, const _3DSLiM_resolution RES) {

	/* Start OPUS 3DCAM Example*/

	/* Step.0: */
	// 0.1 New a 3DCAM handler '_3DCam' and
	// 0.2 declare an output data pointer ' output ' .
	_3DSLiM_API* _3DCam = new _3DSLiM_API();
	_3DSLiM_output_data* output = NULL;


	/* Step. 1: Init _3DCam */
	if (_3DCam->initialize(0) == STATUS_ERROR)
	{
		cout << "Failed to connect to the device, exiting.." << endl;
		return -1;
	}

	/* Step. 2:  Configure RES, and Parameters*/
	// 2.1 Config resolution:  'NOT' support execution time value change.
	//_3DSLiM_resolution const RES = RESOLUTION_640_400; //RESOLUTION_1280_800
	// Note that RESOLUTION_1280_720 is nearly deprecated so might be unuseful
	_3DCam->config_resolution(RES);
	switch(RES)
	{
		case RESOLUTION_1280_720:
			Width = 1280;
			Height = 720;
			num_of_pcd = 80;
			break;
		case RESOLUTION_1280_800:
			Width = 1280;
			Height = 800;
			num_of_pcd = 80;
			break;
		case RESOLUTION_640_400:
		default:
			Width = 640;
			Height = 400;
			num_of_pcd = 320;
			break;
	}

	// 2.2 : set  parameters
	_3DSLiM_parameter param;
	config_parameters(&param); // You can see how to set parameters in this function.
	_3DCam->config_parameter(&param);
	_3DCam->config_exposure(MANUAL, 1000);  // MAX = 3000, set expo value after camera started.

	/* Step. 3:  Start 3D CAM Streaming or OneShot. */
	switch (xfer_mode)
	{
		case STREAMING:
		default:
		{
			// 3.a : Start streaming mode
			cout << "Streaming starts" << endl;
			
			// Check the index of RGB camera, default value of rgb_cam_dev_num is 0
			_3DCam->start(PCD_XYZ, STREAMING);
			_3DCam->config_exposure(AUTO, 100);    //** Auto Exposure is an experimental feature : set auto expo value  after camera started. (second parameter = 100, is target intensity)

			/* Step. 4:  Now 3D-CAM is running, here you can get output data then use it . */
			for (int i = 0; i < num_of_pcd; i++)
			{
				// 4.1 : get output data
				if (_3DCam->get_stream_data(&output) == STATUS_ERROR) // get output data here : 'output' is the data pointer
				{
					cout << "Can't get stream data" << endl;
					_3DCam->release_stream_data(output);
					break;
				}

				// 4.2 : USE DATA @ YOUR CODE.
				/*this function shows how to use data, you can replace this function with yours*/
				use_output_data_example(_3DCam, xfer_mode, output);

				// 4.3 : @the end of  each loop, we should release current data buffer .
				_3DCam->release_stream_data(output);
			}
			break;
		}


		case ONE_SHOT:
		{
			// 3.b : Start oneShot mode
			cout << "One Shot starts" << endl;
			
			// Check the index of RGB camera, default value of rgb_cam_dev_num is 0
			_3DCam->start(PCD_XYZ, ONE_SHOT);
			_3DCam->init_one_shot_buffer(&output);

			/* Step. 4:  Now 3D-CAM is running, here you can get output data then use it . */
			// 4.1 : get output data
			_3DCam->get_one_shot_data(output);

			// 4.2 : USE DATA @ YOUR CODE.
			/*this function shows how to use data, you can replace this function with yours*/
			use_output_data_example(_3DCam, xfer_mode, output);

			// 4.3 :  release current data buffer
			_3DCam->delete_one_shot_buffer(output);

			break;
		}
	}


	/* step. 5 : Finally, if you want to stop 3DCAM, you should release resource by calling "stop" 3DCAM */
	_3DCam->stop();
	cout << "3D CAM stops" << endl;
	delete _3DCam;

	/* End of OPUS 3DCAM Example*/
}


void config_parameters(_3DSLiM_parameter* p_param) {


	/* Quality factor:
	. Setting a higher value to reduce the noise caused by white noise, but will make sensor more sensitive to the sensing range.
	. Integer, value range = (3, 9), default = 7;
	. 'NOT' supports execution time value change.
	*/
	p_param->quality_factor = _3DSLIM_DEFAULT_PAR_QUALITY_FACTOR;

	/* z_cutoff :  Control the sensing range (mini-meter) .
	. Integer,  value range = (0, 2000)mm,  min_z_cutoff default = 30, max_z_cutoff default = 1200;
	. this parameter controls the mapping range of p_depth: min_z_cutoff --> max_z_cutoff  to  65535 -->0.
	. Supports execution time value change.
	*/
	p_param->min_z_cutoff = _3DSLIM_DEFAULT_PAR_MIN_Z_CUTOFF;
	p_param->max_z_cutoff = _3DSLIM_DEFAULT_PAR_MAX_Z_CUTOFF;

	/* sensitivity: Control 3D sensing sensitivity.
	. Setting a higher value makes the sensor more sensitive to the 3D information of object with low reflection.
	. Float, value range = (0, 1.0), default = 0.96.
	. Supports execution time value change.
	*/
	p_param->sensitivity = _3DSLIM_DEFAULT_PAR_SENSITIVITY;

	/* noise_filtering_factor: remove noise points.
	. Float, value range = (0, 1.0), default = 0.15.
	. Value 0 means turn off noise filtering.
	. Supports execution time value change.
	*/
	p_param->noise_filtering_factor = _3DSLIM_DEFAULT_PAR_NOISE_FILTERING_FACTOR;

	/* point_cloud_smoothing_k_size:
	. Odd integer, value = (3, 5, 7 , 9), default = 3.
	. Supports execution time value change.
	*/
	p_param->f_point_cloud_smoothing = _3DSLIM_DEFAULT_PAR_F_POINT_CLOUD_SMOOTHING; // on /off switch
	p_param->point_cloud_smoothing_k_size = _3DSLIM_DEFAULT_PAR_POINT_CLOUD_SMOOTHING_FACTOR;


	/*Experimental feature */
	/* resampling_factor:
	. Setting a higher value will reduce the desnity of point cloud.
	. Float, value range = (0.001, 1.0), default = 0.0025.
	. Supports execution time value change.
	*/
	p_param->f_resampling = _3DSLIM_DEFAULT_PAR_F_RESAMPLING;
	p_param->resampling_factor = _3DSLIM_DEFAULT_PAR_RESAMPLING_FACTOR;

	/*Experimental feature */
	/* threshold_motion_noise_factor:
	. Smaller value will make sensor more sensitive to the motion noise.
	. Float, value range = (0.05, 0.20), default = 0.08.
	. Supports execution time value change.
	*/
	p_param->f_motion_noise_filtering = _3DSLIM_DEFAULT_PAR_F_MOTION_NOISE_FILTERING;
	p_param->threshold_motion_noise_factor = _3DSLIM_DEFAULT_PAR_MOTION_NOISE_FILTERING_FACTOR;

}


void use_output_data_example(_3DSLiM_API* _3DCam, const _3DSLiM_xfer_mode  xfer_mode, _3DSLiM_output_data* output) {

	auto _img_pcd_data = (img_pcd_data*)output->data;
	static int count = 0;

	count++;
	if (count % 100 == 0) {
		// relative information about point cloud
		cout << "n: " << count << endl;
		cout << "effect_num: " << output->effective_num << endl;

		// Example.1: Get point cloud xyz raw data. : _img_pcd_data->pcd_data
		// cout << "Print xyz : " << endl;
		// for (int cnt = 0; cnt < Height * Width; cnt ++)
		// {
		// 	cout << cnt << " ";
		// 	cout << _img_pcd_data->pcd_data[cnt*3] << " ";
		// 	cout << _img_pcd_data->pcd_data[cnt*3+1] << " ";
		// 	cout << _img_pcd_data->pcd_data[cnt*3+2]<< endl;
		// }
	}

	// Example.2: Get IR image data: _img_pcd_data->img_data
	Mat IR_Img(Height, Width, CV_8UC1, _img_pcd_data->img_data);
	imshow("IR_Img", IR_Img);

	// Example.3 : Get 16 bits depth map (z data) : output->p_depth, mapping range of p_depth: min_z_cutoff --> max_z_cutoff  to  65535 -->0.
	// z value = (65535 - depth_value)/ 65535 * (max_z_cutoff - min_z_cutoff) + min_z_cutoff;
	Mat Depth_Map(Height, Width, CV_16UC1, _img_pcd_data->depth_map);
	imshow("16bits depth map", Depth_Map);
	waitKey(10);


	// Capture Images and Pointcloud.
	if ((waitKey_val == 'c') | (waitKey_val == 'C') | (count == num_of_pcd) | (xfer_mode == ONE_SHOT))
	{
		cout << "Capture data: " << count << endl;

		ostringstream temp;

		// Example.4 :  Save depthmap to .PNG.
		temp.str("");
		temp.clear();
		temp << "depth_map_" << count << ".png";
		imwrite(temp.str(), Depth_Map);

		// Example.5 :  Save IR  to .PNG.
		temp.str("");
		temp.clear();
		temp << "IR_Img_" << count << ".png";
		imwrite(temp.str(), IR_Img);

		// Example.6 :  Save point-cloud to .ply format.
		temp.str("");
		temp.clear();
		temp << "xyz_" << count << ".ply";

		_3DCam->save_ply_file(output, temp.str());
		count++;
	}

}
