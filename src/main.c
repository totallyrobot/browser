#include <stdio.h>
#include <gtk/gtk.h>
#include <webkit2/webkit2.h>
#include <glib.h>
#include "urlbar.h"

GtkBuilder *builder;
GtkWidget *windowMain;
GtkWidget *urlBarEntry;
WebKitWebView *viewport;

void openUrl() {
    openFromUrlBar(urlBarEntry, viewport);
}

void refreshUrlBar() {
    refreshUrlBarEntryContent(urlBarEntry, viewport);
}

int main(int argc, char *argv[]) {
	gtk_init(&argc, &argv);
	builder = gtk_builder_new();
	// add the glade file
	gtk_builder_add_from_file(builder, "src/ui/ui.xml", NULL);
    windowMain = GTK_WIDGET(gtk_builder_get_object(builder, "mainWindow"));
    viewport = WEBKIT_WEB_VIEW(webkit_web_view_new());
    urlBarEntry = GTK_WIDGET(gtk_builder_get_object(builder, "urlBarEntry"));
	gtk_builder_connect_signals(builder, NULL);
    g_object_unref(builder);
    gtk_container_add(GTK_CONTAINER(windowMain), GTK_WIDGET(viewport));
    webkit_web_view_load_uri(viewport, "https://github.com/totallyrobot/browser");
    gtk_widget_show_all(windowMain);
    gtk_main();
	return 0;
}