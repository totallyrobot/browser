#include <stdio.h>
#include <gtk/gtk.h>
#include <webkit2/webkit2.h>
#include <glib.h>
#include <unistd.h>
#include <string.h>
#include "urlbar.h"
#include "tabs.h"
#include "signalHandlers.h"
                                                                                                                                                                     
GtkBuilder *builder;
GtkWidget *mainWindow;
GtkWidget *urlBarEntry;
GtkWidget *aboutDialog;
GtkWidget *browserMenu;
GtkWidget *tabBar;

void createNewTab() {
    TRBrowserTab tab = TRBrowser_TRBrowserTab_new();
    gtk_notebook_append_page(GTK_NOTEBOOK(tabBar), GTK_WIDGET(tab.viewport), tab.tabLabel.trBrowserTabLabelContainer);
    gtk_widget_show_all(mainWindow);
    gtk_notebook_set_current_page(GTK_NOTEBOOK(tabBar), -1);
}

void goForward() {
    webkit_web_view_go_forward(getCurrentTab(GTK_NOTEBOOK(tabBar)).viewport);
}

void refreshTab() {
    webkit_web_view_reload(getCurrentTab(GTK_NOTEBOOK(tabBar)).viewport);
}

void refreshCurrentTabUrlBarSignalHandler(WebKitWebView *webview, WebKitLoadEvent loadEvent) {
    refreshCurrentTabUrlBar(loadEvent, GTK_NOTEBOOK(tabBar), urlBarEntry);
}


void refreshTabLabelEventSignalHandlerFavicon(WebKitWebView *webView, WebKitLoadEvent loadEvent) {
    refreshTabLabelHandler(loadEvent, GTK_NOTEBOOK(tabBar), webView, TRUE);
}

void refreshTabLabelEventSignalHandler(WebKitWebView *webView, WebKitLoadEvent loadEvent) {
    refreshTabLabelHandler(loadEvent, GTK_NOTEBOOK(tabBar), webView, FALSE);
}
void refreshTabLabelEventSignalHandlerNotify(WebKitWebView *webView) {
    refreshTabLabelHandler(WEBKIT_LOAD_COMMITTED, GTK_NOTEBOOK(tabBar), webView, FALSE);
}

void refreshUrlBar(GtkNotebook *notebook, GtkWidget *page, guint tabIndex) {
    refreshUrlBarContent(tabIndex, GTK_NOTEBOOK(tabBar), urlBarEntry);
}

void goBack() {
    webkit_web_view_go_back(getCurrentTab(GTK_NOTEBOOK(tabBar)).viewport);
}

void openUrl() {
    openFromUrlBar(urlBarEntry, getCurrentTab(GTK_NOTEBOOK(tabBar)).viewport);
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

void closeCurrentTabSignal() {
    closeCurrentTab(GTK_NOTEBOOK(tabBar));
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
    urlBarEntry = GTK_WIDGET(gtk_builder_get_object(builder, "urlBarEntry"));
	gtk_builder_connect_signals(builder, NULL);
    g_object_unref(builder);
    createNewTab();
    gtk_notebook_remove_page(GTK_NOTEBOOK(tabBar), 0);
    gtk_widget_show_all(mainWindow);
    gtk_main();
	return 0;
}