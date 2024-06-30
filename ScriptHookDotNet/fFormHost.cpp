/*
* Copyright (c) 2009-2011 Hazard (hazard_x@gmx.net / twitter.com/HazardX)
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/

// IV-SDK .NET translation layer by ItsClonkAndre

#include "stdafx.h"

#include "fFormHost.h"

#include "Script.h"

#pragma managed

namespace GTA
{
namespace Forms
{

	// - - - Constructor - - -
	FormHost::FormHost(GTA::Script^ forScript)
	{
		pScript = forScript;
		pForms = gcnew List<Form^>();
	}

	// - - - Properties, Methods and Functions - - -
	void FormHost::Add(Form^ form)
	{
		if isNULL(form)
			return;
		if (pForms->Contains(form))
			return;

		pForms->Add(form);
	}
	void FormHost::Remove(Form^ form)
	{
		if isNULL(form)
			return;

		pForms->Remove(form);
	}

	void FormHost::Draw()
	{
		for (int i = 0; i < pForms->Count; i++)
		{
			pForms[i]->OnPaint();
		}
	}

}
}