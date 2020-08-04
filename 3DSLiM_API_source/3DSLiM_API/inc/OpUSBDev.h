#ifndef OpUSBDev_H
#define OpUSBDev_H

#ifdef OPUSBDEV_EXPORT
#define OPUSBDEV_FUNC   __declspec(dllexport)
#else
#define OPUSBDEV_FUNC
#endif

/* Enumeration for return status */
typedef enum
{
	STATUS_ERROR = 0,
	STATUS_OK
}return_status;

/* Class definition and exported functions -----------------------------------*/
class OPUSBDEV_FUNC OpUSBDev
{
public:
	virtual return_status initialize(int dev_num) = 0;

	friend class Eng_API;

protected:
	void* handle;
};

#endif