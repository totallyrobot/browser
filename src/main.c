#include <stdio.h>
#include <gtk/gtk.h>
#include <webkit2/webkit2.h>
#include <glib.h>
#include <unistd.h>
#include <string.h>
#include "urlbar.h"
#include "tabs.h"
                                                                                                                                                                     
GtkBuilder *builder;
GtkWidget *mainWindow;
GtkWidget *urlBarEntry;
GtkWidget *aboutDialog;
GtkWidget *browserMenu;
GtkWidget *tabBar;
TRBrowserTab tab1;
TRBrowserTab tab2;

void createNewTab() {
    TRBrowserTab tab = TRBrowser_TRBrowserTab_new();
    gtk_notebook_append_page(GTK_NOTEBOOK(tabBar), GTK_WIDGET(tab.viewport), NULL);
    gtk_widget_show_all(mainWindow);
}

void goForward() {
    webkit_web_view_go_forward(tab1.viewport);
}

void goBack() {
    webkit_web_view_go_back(tab1.viewport);
}

void openUrl() {
    openFromUrlBar(urlBarEntry, tab1.viewport);
}

//void refreshUrlBar() {
//    refreshUrlBarEntryContent(urlBarEntry, tab1.viewport);
//}

void openBrowserMenu() {
    gtk_widget_show_all(browserMenu);
}

void openAboutDialog() {
    gtk_dialog_run(GTK_DIALOG(aboutDialog));
}

void exitApp() {
    exit(0);
}

int main(int argc, char *argv[]) {
	gtk_init(&argc, &argv);
	builder = gtk_builder_new();
	// add the glade file
	gtk_builder_add_from_file(builder, "src/ui/ui.xml", NULL);
    mainWindow = GTK_WIDGET(gtk_builder_get_object(builder, "mainWindow"));
    aboutDialog = GTK_WIDGET(gtk_builder_get_object(builder, "aboutDialog"));
    browserMenu = GTK_WIDGET(gtk_builder_get_object(builder, "browserMenu"));
    tabBar = GTK_WIDGET(gtk_builder_get_object(builder, "tabBar"));
    tab1 = TRBrowser_TRBrowserTab_new();
    tab2 = TRBrowser_TRBrowserTab_new();
    urlBarEntry = GTK_WIDGET(gtk_builder_get_object(builder, "urlBarEntry"));
	gtk_builder_connect_signals(builder, NULL);
    g_object_unref(builder);
    createNewTab();
    gtk_notebook_append_page(GTK_NOTEBOOK(tabBar), GTK_WIDGET(tab1.viewport), NULL);
    gtk_notebook_append_page(GTK_NOTEBOOK(tabBar), GTK_WIDGET(tab2.viewport), NULL);
    webkit_web_view_load_uri(tab2.viewport, "https://github.com/totallyrobot/browser");
    webkit_web_view_load_uri(tab1.viewport, "https://github.com/totallyrobot");
    gtk_widget_show_all(mainWindow);
    gtk_main();
	return 0;
}