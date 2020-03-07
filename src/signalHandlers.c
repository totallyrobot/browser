#include <gtk/gtk.h>
#include <webkit2/webkit2.h>
#include "urlbar.h"

void refreshCurrentTabUrlBar(WebKitLoadEvent loadEvent, GtkNotebook *tabBar, GtkWidget *urlBarEntry) {
    switch (loadEvent) {
        case WEBKIT_LOAD_STARTED:
            refreshUrlBarContent(gtk_notebook_get_current_page(GTK_NOTEBOOK(tabBar)), GTK_NOTEBOOK(tabBar), urlBarEntry);
        break;
		case WEBKIT_LOAD_REDIRECTED:
			refreshUrlBarContent(gtk_notebook_get_current_page(GTK_NOTEBOOK(tabBar)), GTK_NOTEBOOK(tabBar), urlBarEntry);
		break;
		case WEBKIT_LOAD_COMMITTED:
			refreshUrlBarContent(gtk_notebook_get_current_page(GTK_NOTEBOOK(tabBar)), GTK_NOTEBOOK(tabBar), urlBarEntry);
		break;
    }
}