#include <gtk/gtk.h>
#include <webkit2/webkit2.h>
#include "urlbar.h"
#include "tabs.h"

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

void refreshTabLabelHandler(WebKitLoadEvent loadEvent, GtkNotebook *tabBar, WebKitWebView *viewport, gboolean forFavicon) {
	/*switch (loadEvent) {
		case WEBKIT_LOAD_COMMITTED:
			refreshTabLabel(gtk_notebook_page_num(tabBar, GTK_WIDGET(viewport)), tabBar, forFavicon, loadEvent);
		break;
		case WEBKIT_LOAD_FINISHED:
			refreshTabLabel(gtk_notebook_page_num(tabBar, GTK_WIDGET(viewport)), tabBar, forFavicon, loadEvent);
		break;
		case WEBKIT_LOAD_STARTED:
			refreshTabLabel(gtk_notebook_page_num(tabBar, GTK_WIDGET(viewport)), tabBar, forFavicon, loadEvent);
		break;
    }*/
	refreshTabLabel(gtk_notebook_page_num(tabBar, GTK_WIDGET(viewport)), tabBar, forFavicon, loadEvent);
}
void updateSpinnerHandler(WebKitLoadEvent loadEvent, GtkNotebook *tabBar, WebKitWebView *viewport) {
	switch (loadEvent) {
		case WEBKIT_LOAD_FINISHED:
			tabSpinnerUpdate(gtk_notebook_page_num(tabBar, GTK_WIDGET(viewport)), tabBar, loadEvent);
		break;
		case WEBKIT_LOAD_STARTED:
			tabSpinnerUpdate(gtk_notebook_page_num(tabBar, GTK_WIDGET(viewport)), tabBar, loadEvent);
		break;
    }	
}