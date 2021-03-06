/* -*- Mode: c++; c-basic-offset: 2; indent-tabs-mode: nil; tab-width: 40 -*- */
/* vim: set ts=2 et sw=2 tw=40: */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef mozilla_dom_voicemail_voicemail_h__
#define mozilla_dom_voicemail_voicemail_h__

#include "nsDOMEvent.h"
#include "nsDOMEventTargetHelper.h"
#include "nsIDOMMozVoicemail.h"
#include "nsIRadioInterfaceLayer.h"

class nsPIDOMWindow;
class nsIRILContentHelper;
class nsIDOMMozVoicemailStatus;

namespace mozilla {
namespace dom {

class Voicemail : public nsDOMEventTargetHelper,
                  public nsIDOMMozVoicemail
{
public:
  NS_DECL_ISUPPORTS_INHERITED
  NS_DECL_NSIDOMMOZVOICEMAIL
  NS_DECL_NSIRILVOICEMAILCALLBACK

  NS_FORWARD_NSIDOMEVENTTARGET(nsDOMEventTargetHelper::)

  Voicemail(nsPIDOMWindow* aWindow, nsIRILContentHelper* aRIL);
  virtual ~Voicemail();

private:
  nsCOMPtr<nsIRILContentHelper> mRIL;
  nsCOMPtr<nsIRILVoicemailCallback> mRILVoicemailCallback;

  class RILVoicemailCallback : public nsIRILVoicemailCallback
  {
    Voicemail* mVoicemail;

  public:
    NS_DECL_ISUPPORTS
    NS_FORWARD_NSIRILVOICEMAILCALLBACK(mVoicemail->)

    RILVoicemailCallback(Voicemail* aVoicemail)
    : mVoicemail(aVoicemail)
    {
      NS_ASSERTION(mVoicemail, "Null pointer!");
    }
  };
};

} // namespace dom
} // namespace mozilla

nsresult
NS_NewVoicemail(nsPIDOMWindow* aWindow, nsIDOMMozVoicemail** aVoicemail);

#endif // mozilla_dom_voicemail_voicemail_h__
