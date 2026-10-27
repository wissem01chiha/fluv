/**
 * Copyright 2026 Wissem Chiha
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License. 
 */
#ifndef FVERRNO_H
#define FVERRNO_H

#include "fluv/fvtypes.h"

typedef enum {
    FV_SUCCESS = 0,
    FV_ERROR_UNKNOWN = -1,
    FV_ERROR_INVALID_ARGUMENT = -2,
    FV_ERROR_OUT_OF_MEMORY = -3,
    FV_ERROR_NOT_FOUND = -4
} fv_error_t;

#endif // FVERRNO_H