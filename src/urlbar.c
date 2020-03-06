#include <gtk/gtk.h>
#include <webkit2/webkit2.h>

void openFromUrlBar(GtkWidget *urlBar, WebKitWebView *webview) {
    const gchar *input = gtk_entry_get_text(GTK_ENTRY(urlBar));
    webkit_web_view_load_uri(webview, input);
}

// NOTE: this function if called if:
// the tab in the GtkNotebook changes
// or
// the tab loads a new page
void refreshUrlBarContent(GtkNotebook *tabBar) {
;
}