/*******************************************************************************
 * @file   Main.hpp
 * @author Brian Hoffpauir
 * @date   02.08.2023
 * @brief  Application entry point.
 *
 * Copyright (c) 2023, Brian Hoffpauir All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 ******************************************************************************/
#include "LexiStd.hpp"

#include <X11/Xlib.h>

using namespace Lexi;
using namespace tinyxml2;

static XMLElement *LoadConfig(XMLDocument &xmlDoc);

int main(int numArgs, char *pArgs[]) try
{
	XMLDocument xmlDoc;
	auto *pRoot = LoadConfig(xmlDoc);

	Config &config = Config::Get();
	Logger &logger = Logger::Get();
	config.Load(pRoot);
	logger.Init(pRoot->FirstChildElement("Logging"));
	//std::ofstream outFile(logger.GetSystemTime(true).value() + "_lexi_log.txt");
	//logger.RedirectLevelTo(Logger::Level::Msg, outFile);
	//logger.RedirectLevelTo(Logger::Level::Err, outFile);
	
	LEXI_LOG("Starting application...");
	
	LEXI_LOG("Program name: {}", config.GetApp().programName);
	LEXI_LOG("Description: {}", config.GetApp().description);
	LEXI_LOG("Long description: {}", config.GetApp().longDesc);
	LEXI_LOG("Operating system: {}", Config::OperatingSystemToString(config.GetApp().OS));
	
	UniqueICommandPtr pCommand = std::make_unique<QuitCommand>();
	pCommand->VExecute();

	UniqueSpellCheckVisitorPtr pSpellChecker = std::make_unique<SpellCheckVisitor>();
	std::string test = "What's up dood?";

	for (auto ch : test)
	{
		pSpellChecker->VVisitCharacter(ch);
	}

	for (const auto &kMisspelling : pSpellChecker->GetMisspellings())
	{
		LEXI_LOG("Misspelled: '{}'", kMisspelling);
	}

	Display *pDisplay = nullptr;
	Window window;
	XEvent event;
	constexpr std::string_view kMESSAGE = "Hello, world!";
	int defaultScreen = 0;

	pDisplay = XOpenDisplay(nullptr);
	if (!pDisplay)
	{
		LEXI_THROW("Cannot open display!");
	}

	defaultScreen = DefaultScreen(pDisplay);

	window = XCreateSimpleWindow(pDisplay, RootWindow(pDisplay, defaultScreen),
								 10, 10, 800, 600, 1,
								 BlackPixel(pDisplay, defaultScreen),
								 WhitePixel(pDisplay, defaultScreen));

	XStoreName(pDisplay, window, config.GetApp().programName.c_str());
	XSelectInput(pDisplay, window, ExposureMask | KeyPressMask);

	XMapWindow(pDisplay, window);

	bool bRunning = true;
	while (bRunning)
	{
		XNextEvent(pDisplay, &event);

		switch (event.type)
		{
		case Expose:
			XFillRectangle(pDisplay, window,
						   DefaultGC(pDisplay, defaultScreen),
						   20, 20, 10, 10);
			XDrawString(pDisplay, window,
						DefaultGC(pDisplay, defaultScreen),
						50, 50, kMESSAGE.data(), kMESSAGE.size());
			break;
		case KeyPress:
			bRunning = false;
			break;
		}
	}

	XCloseDisplay(pDisplay);
	
	config.Save(pRoot);
	
	LEXI_LOG("Quitting application...");
	return 0;
}
catch (const Exception &kExcept)
{
	LEXI_ERR("Exception occured({}:{}): {}", kExcept.GetFilename(), kExcept.GetLineNum(), kExcept.VWhat());
}
catch (const std::exception &kExcept)
{
	LEXI_ERR("Exception occured: {}", kExcept.what());
}

XMLElement *LoadConfig(XMLDocument &xmlDoc)
{
	XMLError xmlResult = xmlDoc.LoadFile("Config.xml");
	LEXI_THROW_IF(xmlResult != XML_SUCCESS, "Couldn't load the config file!");
	
	XMLElement *pRoot = xmlDoc.RootElement();
	LEXI_THROW_IF(!pRoot, "No root config element!");
	return pRoot;
}

