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

#include <gtk/gtk.h>

using namespace Lexi;

static void Click(GtkWidget *pWidget, gpointer pUserData)
{
	LEXI_MSG("Button clicked!");
}

static void Activate(GtkApplication *pApp,
					 gpointer pUserData)
{
	GtkWidget *pWindow = gtk_application_window_new(pApp);

	gtk_window_set_title(GTK_WINDOW(pWindow), "sample_doc.lexi - Lexi");
	gtk_window_set_default_size(GTK_WINDOW(pWindow), 800, 600);

	GtkWidget *pButton = gtk_button_new_with_label("Hello, world!");
	g_signal_connect(pButton, "clicked", G_CALLBACK(Click), NULL);
	gtk_window_set_child(GTK_WINDOW(pWindow), pButton);
	
	gtk_window_present(GTK_WINDOW(pWindow));
}

int main(int numArgs, char *pArgs[]) try
{
	//std::ofstream outFile(Logger::Get().GetSystemTime(true).value() + "_lexi_log.txt");
	//Logger::Get().RedirectLevelTo(Logger::Level::Msg, outFile);
	//Logger::Get().RedirectLevelTo(Logger::Level::Err, outFile);
	
	Logger::Get().SetWrapCount(72);
	LEXI_MSG("Starting application...");

	LEXI_ERR("Uh oh error!");

	GtkApplication *pApp = nullptr;
	int status = EXIT_SUCCESS;

	pApp = gtk_application_new("lexi",
							   G_APPLICATION_DEFAULT_FLAGS);
	g_signal_connect(pApp, "activate",
					 G_CALLBACK(Activate), NULL);
	status = g_application_run(G_APPLICATION(pApp), numArgs, pArgs);
	g_object_unref(pApp);
	
	LEXI_MSG("Quitting application...");
	//LEXI_THROW("Uh oh.");
	//return status;
	return 0;
}
catch (const Exception &kExcept)
{
	std::cerr << "Exception occured: " << kExcept.VWhat() << '\n';
}
catch (const std::exception &kExcept)
{
	std::cerr << "Exception occured: " << kExcept.what() << '\n';
}

