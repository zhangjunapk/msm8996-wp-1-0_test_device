#ifndef __GP_COMM_INTF_H
#define __GP_COMM_INTF_H

/* ------------------------------------------------------------------------
 * Include files
 * ------------------------------------------------------------------------ */
#include "gpTypes.h"

/* ------------------------------------------------------------------------
 * External Variable Declarations
 * ------------------------------------------------------------------------ */
typedef struct qsee_gp_opensession_req_type_t {
  TEE_UUID    uuid;
  uint32_t    connectionMethod;
  uint32_t    connectionData;
  uint32_t    paramTypes;
  TEE_Param   params[MAX_GP_PARAMS];
} qsee_gp_opensession_req_type;

typedef struct qsee_gp_invokecommand_req_type_t {
  uint32_t    sessionId;
  uint32_t    appCommandId;
  uint32_t    paramTypes;
  TEE_Param   params[MAX_GP_PARAMS];
} qsee_gp_invokecommand_req_type;

typedef struct qsee_gp_closesession_req_type_t {
  uint32_t    sessionId;
} qsee_gp_closesession_req_type;

//GP Request Cancellation Type
typedef struct qsee_gp_requestcancellation_req_type_t {
  uint32_t      sessionId;
  uint32_t      paramTypes;
  TEE_Param     params[MAX_GP_PARAMS];
} qsee_gp_requestcancellation_req_type;

//GP Response Type
typedef struct qsee_gp_command_response_type_t {
  uint32_t    app_id;
  uint32_t    sessionId;
  TEE_Result    teeResult;
  uint32_t    returnOrigin;
} qsee_gp_command_response_type;

//Listener svc req msg sent from TA
typedef struct qsee_gp_reqcancel_req_type_t {
  uint32_t    session_id;
  uint32_t    timeout;
  bool        maskcancellation;
} __attribute__ ((packed)) qsee_gp_reqcancel_req_type;

//Listener svc rsp msg sent to TA
typedef struct qsee_gp_reqcancel_rsp_type_t {
  uint32_t    session_id;
  uint32_t    result;
} __attribute__ ((packed)) qsee_gp_reqcancel_rsp_type;

#endif /* __GP_COMM_INTF_H */
