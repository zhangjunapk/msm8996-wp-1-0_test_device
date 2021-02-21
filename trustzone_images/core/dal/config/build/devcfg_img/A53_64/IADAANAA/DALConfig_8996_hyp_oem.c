#include "DALPropDef.h"
#include "DALDeviceId.h"
#include "dalconfig.h"
#include "dalconfig.h"
#include "customer.h"
#include "customer.h"
#include "custiadaanaaa.h"
#include "custiadaanaaa.h"
#include "targiadaanaaa.h"
#include "custiadaanaaa.h"
#include "custiadaanaaa.h"
#include "custremoteapis.h"
#include "custiadaanaaa.h"
#include "custtarget.h"
#include "custiadaanaaa.h"
#include "custsdcc.h"
#include "custiadaanaaa.h"
#include "custsurf.h"
#include "custiadaanaaa.h"
#include "custdiag.h"
#include "custiadaanaaa.h"
#include "custefs.h"
#include "custiadaanaaa.h"
#include "custpmic.h"
#include "custiadaanaaa.h"
#include "custsio_8660.h"
#include "custiadaanaaa.h"
#include "custsec.h"
#include "custsec.h"
#include "custsfs.h"
#include "custsec.h"
#include "custiadaanaaa.h"
#include "customer.h"
#include "dalconfig.h"
#include "QupACCommonIds.h"
#include "comdef.h"
#include "com_dtypes.h"
#include "stdint.h"
#include "alltypes.h"
#include "target.h"
#include "customer.h"
#include "custiadaanaaa.h"
#include "targiadaanaaa.h"
#include "custremoteapis.h"
#include "custtarget.h"
#include "custsdcc.h"
#include "custsurf.h"
#include "custdiag.h"
#include "custefs.h"
#include "custpmic.h"
#include "custsio_8660.h"
#include "custsec.h"
#include "custsfs.h"
#include "armasm.h"
#include "DALStdDef.h" 
#include "DALSysTypes.h" 

#ifndef DAL_CONFIG_IMAGE_APPS 
#define DAL_CONFIG_IMAGE_APPS 
#endif 
extern void * pm_hyp_spmi_cfg_8996_xml_hyp;
extern void * pm_hyp_spmi_cfg_sz_8996_xml_hyp;

const DALSYSPropStructTblType DALPROP_StructPtrs_8996_xml_hyp[3] =  {
	 {sizeof(void *), &pm_hyp_spmi_cfg_8996_xml_hyp},
	 {sizeof(void *), &pm_hyp_spmi_cfg_sz_8996_xml_hyp},
	{0, 0 } 
 };
const uint32 DALPROP_PropBin_8996_xml_hyp[] = {

			0x000006c4, 0x00000020, 0x00000290, 0x00000290, 0x00000290, 
			0x00000001, 0x00000001, 0x00000690, 0x49524550, 0x49204850, 
			0x50470044, 0x72204f49, 0x65676e61, 0x5f575200, 0x45434341, 
			0x4c5f5353, 0x00545349, 0x49524550, 0x425f4850, 0x3150534c, 
			0x5f505551, 0x495f4752, 0x5845444e, 0x4154535f, 0x50005452, 
			0x50495245, 0x4c425f48, 0x51325053, 0x525f5055, 0x4e495f47, 
			0x5f584544, 0x52415453, 0x45500054, 0x48504952, 0x534c425f, 
			0x41553150, 0x525f5452, 0x4e495f47, 0x5f584544, 0x52415453, 
			0x45500054, 0x48504952, 0x534c425f, 0x41553250, 0x525f5452, 
			0x4e495f47, 0x5f584544, 0x52415453, 0x53530054, 0x4c425f43, 
			0x55515053, 0x47525f50, 0x444e495f, 0x535f5845, 0x54524154, 
			0x43535300, 0x534c425f, 0x52415550, 0x47525f54, 0x444e495f, 
			0x535f5845, 0x54524154, 0x52455000, 0x5f485049, 0x4f495047, 
			0x5f47525f, 0x45444e49, 0x54535f58, 0x00545241, 0x5f4d554e, 
			0x49524550, 0x425f4850, 0x5f50534c, 0x45524f43, 0x554e0053, 
			0x4c425f4d, 0x4d5f5053, 0x43494e49, 0x5345524f, 0x4d554e00, 
			0x4353535f, 0x4e494d5f, 0x524f4349, 0x50005345, 0x50495245, 
			0x53535f48, 0x534c425f, 0x425f3150, 0x5f50534c, 0x204d4142, 
			0x45534142, 0x52455000, 0x5f485049, 0x425f5353, 0x3250534c, 
			0x534c425f, 0x41425f50, 0x4142204d, 0x53004553, 0x425f4353, 
			0x5f50534c, 0x50534c42, 0x4d41425f, 0x53414220, 0x45500045, 
			0x48504952, 0x5f53535f, 0x50534c42, 0x41425f31, 0x5049504d, 
			0x49535f45, 0x4e495f44, 0x5f584544, 0x52415453, 0x45500054, 
			0x48504952, 0x5f53535f, 0x50534c42, 0x41425f32, 0x5049504d, 
			0x49535f45, 0x4e495f44, 0x5f584544, 0x52415453, 0x53530054, 
			0x4c425f43, 0x425f5053, 0x49504d41, 0x535f4550, 0x495f4449, 
			0x5845444e, 0x4154535f, 0x50005452, 0x50495245, 0x53535f48, 
			0x534c425f, 0x4d535f50, 0x495f554d, 0x4154534e, 0x0045434e, 
			0x5f435353, 0x50534c42, 0x4d4d535f, 0x4e495f55, 0x4e415453, 
			0x44004543, 0x6e456c61, 0x61540076, 0x74656772, 0x00676643, 
			0x61736964, 0x5f656c62, 0x756d6d73, 0x0063615f, 0x696d7073, 
			0x6168635f, 0x6c656e6e, 0x6766635f, 0x6d707300, 0x68635f69, 
			0x656e6e61, 0x66635f6c, 0x69735f67, 0x0000657a, 0x00000001, 
			0x00008996, 0x00002070, 0x02800000, BLSP1_QUP0, 0x0880000a, 
			0x02010003, 0x00000003, 0x08800015, 0x00000300, 0xff00ff00, 
			0x02800000, BLSP1_UART0, 0x0880000a, 0x00000000, 0x08800015, 
			0x0000ff00, 0xff00ff00, 0x02800000, BLSP1_QUP1, 0x0880000a, 
			0x00000000, 0x08800015, 0x00000300, 0xff00ff00, 0x02800000, 
			BLSP1_UART1, 0x0880000a, 0x00000000, 0x08800015, 0x00000300, 
			0xff00ff00, 0x02800000, BLSP1_QUP2, 0x0880000a, 0x2f2e2d03, 
			0x00000030, 0x08800015, 0x00000300, 0xff00ff00, 0x02800000, 
			BLSP1_UART2, 0x0880000a, 0x00000000, 0x08800015, 0x00000600, 
			0xff00ff00, 0x02800000, BLSP1_QUP3, 0x0880000a, 0x00000000, 
			0x08800015, 0x0000ff00, 0xff00ff00, 0x02800000, BLSP1_UART3, 
			0x0880000a, 0x00000000, 0x08800015, 0x0000ff00, 0xff00ff00, 
			0x02800000, BLSP1_QUP4, 0x0880000a, 0x00000000, 0x08800015, 
			0x00000600, 0xff00ff00, 0x02800000, BLSP1_UART4, 0x0880000a, 
			0x00000000, 0x08800015, 0x00000600, 0xff00ff00, 0x02800000, 
			BLSP1_QUP5, 0x0880000a, 0x00000000, 0x08800015, 0x00000300, 
			0xff00ff00, 0x02800000, BLSP1_UART5, 0x0880000a, 0x00000000, 
			0x08800015, 0x0000ff00, 0xff00ff00, 0x02800000, BLSP2_QUP0, 
			0x0880000a, 0x00000000, 0x08800015, 0x00000300, 0xff00ff00, 
			0x02800000, BLSP2_UART0, 0x0880000a, 0x00000000, 0x08800015, 
			0x0000ff00, 0xff00ff00, 0x02800000, BLSP2_QUP1, 0x0880000a, 
			0x06050403, 0x00000007, 0x08800015, 0x00000300, 0xff00ff00, 
			0x02800000, BLSP2_UART1, 0x0880000a, 0x00000000, 0x08800015, 
			0x00000300, 0xff00ff00, 0x02800000, BLSP2_QUP2, 0x0880000a, 
			0x33323103, 0x00000034, 0x08800015, 0x0000ff00, 0xff00ff00, 
			0x02800000, BLSP2_UART2, 0x0880000a, 0x00000000, 0x08800015, 
			0x0000ff00, 0xff00ff00, 0x02800000, BLSP2_QUP3, 0x0880000a, 
			0x0a090803, 0x0000000b, 0x08800015, 0x0000ff00, 0xff00ff00, 
			0x02800000, BLSP2_UART3, 0x0880000a, 0x00000000, 0x08800015, 
			0x0000ff00, 0xff00ff00, 0x02800000, BLSP2_QUP4, 0x0880000a, 
			0x00000000, 0x08800015, 0x0000ff00, 0xff00ff00, 0x02800000, 
			BLSP2_UART4, 0x0880000a, 0x00000000, 0x08800015, 0x0000ff00, 
			0xff00ff00, 0x02800000, BLSP2_QUP5, 0x0880000a, 0x57565503, 
			0x00000058, 0x08800015, 0x00000300, 0xff00ff00, 0x02800000, 
			BLSP2_UART5, 0x0880000a, 0x00000000, 0x08800015, 0x0000ff00, 
			0xff00ff00, 0x02800000, SSC_QUP0, 0x0880000a, 0x00000000, 
			0x08800015, 0x0000ff00, 0xff00ff00, 0x02800000, SSC_UART0, 
			0x0880000a, 0x00000000, 0x08800015, 0x0000ff00, 0xff00ff00, 
			0x02800000, SSC_QUP1, 0x0880000a, 0x00000000, 0x08800015, 
			0x0000ff00, 0xff00ff00, 0x02800000, SSC_UART1, 0x0880000a, 
			0x00000000, 0x08800015, 0x0000ff00, 0xff00ff00, 0x02800000, 
			SSC_QUP2, 0x0880000a, 0x00000000, 0x08800015, 0x0000ff00, 
			0xff00ff00, 0x02800000, SSC_UART2, 0x0880000a, 0x00000000, 
			0x08800015, 0x0000ff00, 0xff00ff00, 0x02800024, 0x0000000d, 
			0x02800043, 0x0000000d, 0x02800062, 0x00000007, 0x02800082, 
			0x00000007, 0x028000a2, 0x0000000a, 0x028000bd, 0x00000007, 
			0x028000d9, 0x00000000, 0x028000f4, 0x00000002, 0x0280010a, 
			0x00000006, 0x0280011d, 0x00000003, 0x0280012f, 0x07544000, 
			0x0280014d, 0x07584000, 0x0280016b, 0x01e84000, 0x02800182, 
			0x00000080, 0x028001aa, 0x000000c0, 0x028001d2, 0x00000008, 
			0x028001f3, 0x00000018, 0x02800210, 0x00000019, 0xff00ff00, 
			0x02800227, 0x80000002, 0x1480022e, 0x00000000, 0xff00ff00, 
			0x02800238, 0x00000000, 0xff00ff00, 0x12800248, 0x00000000, 
			0x12800259, 0x00000001, 0xff00ff00 };



const StringDevice driver_list_8996_xml_hyp[] = {
			{"/dev/buses/qup/blsp1_qup0",2346008095u, 668, NULL, 0, NULL },
			{"/dev/buses/uart/blsp1_uart0",2428797227u, 700, NULL, 0, NULL },
			{"/dev/buses/qup/blsp1_qup1",2346008096u, 728, NULL, 0, NULL },
			{"/dev/buses/uart/blsp1_uart1",2428797228u, 756, NULL, 0, NULL },
			{"/dev/buses/qup/blsp1_qup2",2346008097u, 784, NULL, 0, NULL },
			{"/dev/buses/uart/blsp1_uart2",2428797229u, 816, NULL, 0, NULL },
			{"/dev/buses/qup/blsp1_qup3",2346008098u, 844, NULL, 0, NULL },
			{"/dev/buses/uart/blsp1_uart3",2428797230u, 872, NULL, 0, NULL },
			{"/dev/buses/qup/blsp1_qup4",2346008099u, 900, NULL, 0, NULL },
			{"/dev/buses/uart/blsp1_uart4",2428797231u, 928, NULL, 0, NULL },
			{"/dev/buses/qup/blsp1_qup5",2346008100u, 956, NULL, 0, NULL },
			{"/dev/buses/uart/blsp1_uart5",2428797232u, 984, NULL, 0, NULL },
			{"/dev/buses/qup/blsp2_qup0",2385143488u, 1012, NULL, 0, NULL },
			{"/dev/buses/uart/blsp2_uart0",3720265196u, 1040, NULL, 0, NULL },
			{"/dev/buses/qup/blsp2_qup1",2385143489u, 1068, NULL, 0, NULL },
			{"/dev/buses/uart/blsp2_uart1",3720265197u, 1100, NULL, 0, NULL },
			{"/dev/buses/qup/blsp2_qup2",2385143490u, 1128, NULL, 0, NULL },
			{"/dev/buses/uart/blsp2_uart2",3720265198u, 1160, NULL, 0, NULL },
			{"/dev/buses/qup/blsp2_qup3",2385143491u, 1188, NULL, 0, NULL },
			{"/dev/buses/uart/blsp2_uart3",3720265199u, 1220, NULL, 0, NULL },
			{"/dev/buses/qup/blsp2_qup4",2385143492u, 1248, NULL, 0, NULL },
			{"/dev/buses/uart/blsp2_uart4",3720265200u, 1276, NULL, 0, NULL },
			{"/dev/buses/qup/blsp2_qup5",2385143493u, 1304, NULL, 0, NULL },
			{"/dev/buses/uart/blsp2_uart5",3720265201u, 1336, NULL, 0, NULL },
			{"/dev/buses/qup/ssc_qup0",4266220230u, 1364, NULL, 0, NULL },
			{"/dev/buses/uart/ssc_uart0",2125900082u, 1392, NULL, 0, NULL },
			{"/dev/buses/qup/ssc_qup1",4266220231u, 1420, NULL, 0, NULL },
			{"/dev/buses/uart/ssc_uart1",2125900083u, 1448, NULL, 0, NULL },
			{"/dev/buses/qup/ssc_qup2",4266220232u, 1476, NULL, 0, NULL },
			{"/dev/buses/uart/ssc_uart2",2125900084u, 1504, NULL, 0, NULL },
			{"BLSP_GLOBAL_PROP",3648527686u, 1532, NULL, 0, NULL },
			{"/ac/smmu",4045178921u, 1700, NULL, 0, NULL },
			{"/pmic/hyp/cfg",2933554588u, 1712, NULL, 0, NULL }
};
