

#ifndef WEBSERVER_STATUS_CODES_H
#define WEBSERVER_STATUS_CODES_H

// 100
#define STATUSCODE_CONTINUE_HEADER          "100 Continue"
#define STATUSCODE_CONTINUE_BODY            ""


// 200
#define STATUSCODE_OK_SUCCESS_HEADER        "200 OK"
#define STATUSCODE_OK_SUCCESS_BODY          ""

#define STATUSCODE_CREATED_HEADER           "201 Created"
#define STATUSCODE_CREATED_BODY             ""

#define STATUSCODE_ACCEPTED_HEADER          "202 Accepted"
#define STATUSCODE_ACCEPTED_BODY            ""


//400
#define STATUSCODE_BADREQUEST_HEADER        "400 Bad Request"
#define STATUSCODE_BADREQUEST_BODY          "Bad Request!"

#define STATUSCODE_UNAUTHORIZED_HEADER      "401 Unauthorized"
#define STATUSCODE_UNAUTHORIZED_BODY        "Unauthorized!"

#define STATUSCODE_FORBIDDEN_HEADER         "403 Forbidden"
#define STATUSCODE_FORBIDDEN_BODY           "Forbidden!"

#define STATUSCODE_NOTFOUND_HEADER          "404 Not Found"
#define STATUSCODE_NOTFOUND_BODY            "Page Not found!"


// 500
#define STATUSCODE_INTERNALSERVERERROR_HEADER   "500 Internal Server Error"
#define STATUSCODE_INTERNALSERVERERROR_BODY     "Internal Server Error"

#define STATUSCODE_BADGATEWAY_HEADER        "502 Bad Gateway"
#define STATUSCODE_BADGATEWAY_BODY          "Bad Gateway!"

#define STATUSCODE_SERVICEUNAVAILABLE_HEADER   "503 Service Unavailable"
#define STATUSCODE_SERVICEUNAVAILABLE_BODY     "Service Unavailable!"


#endif //WEBSERVER_STATUS_CODES_H
