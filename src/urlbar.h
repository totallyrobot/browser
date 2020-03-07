#ifndef HEADER_FILE
#define HEADER_FILE
void openFromUrlBar(GtkWidget *urlBar, WebKitWebView *webview);
void refreshUrlBarContent(guint TabIndex, GtkNotebook *tabBar, GtkWidget *urlBar);
#endif