#include <gtk/gtk.h>
#include <webkit2/webkit2.h>

void openFromUrlBar(GtkWidget *urlBar, WebKitWebView *webview) {
    const gchar *input = gtk_entry_get_text(GTK_ENTRY(urlBar));
    webkit_web_view_load_uri(webview, input);
}

void refreshUrlBarEntryContent(GtkWidget *urlBar, WebKitWebView *webview) {
        gtk_entry_set_text(GTK_ENTRY(urlBar), webkit_web_view_get_uri(webview));
}