/*
Copyright 2024 Intel Corporation

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef KVM_AUDIO_H
#define KVM_AUDIO_H

#if defined(_KVM_AUDIO)

#include "microstack/ILibParsers.h"

/*
 * kvm_audio_init - called once at kvm_relay_setup time.
 *   writeHandler : the same function pointer used by the KVM relay to send
 *                  data back to the browser; the audio thread calls it to
 *                  push MNG_AUDIO_DATA / MNG_AUDIO_CAPS frames.
 *   reserved     : opaque user context forwarded to writeHandler.
 *
 * Sends MNG_AUDIO_CAPS to the browser immediately (capability advertisement).
 * Audio capture is NOT started until kvm_audio_start() is called.
 */
void kvm_audio_init(ILibTransport_DoneState(*writeHandler)(char*, int, void*), void *reserved);

/*
 * kvm_audio_start - spawns the capture thread; called on receipt of
 *                   MNG_AUDIO_START (cmd 92) from the browser.
 */
void kvm_audio_start(void);

/*
 * kvm_audio_stop  - signals the capture thread to exit and waits for it;
 *                   called on MNG_AUDIO_STOP (cmd 93) and from kvm_cleanup().
 */
void kvm_audio_stop(void);

#endif /* _KVM_AUDIO */

#endif /* KVM_AUDIO_H */
