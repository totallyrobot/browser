void refreshCurrentTabUrlBar(WebKitLoadEvent loadEvent, GtkNotebook *tabBar, GtkWidget *urlBarEntry);
void refreshTabLabelHandler(WebKitLoadEvent loadEvent, GtkNotebook *tabBar, WebKitWebView *viewport, gboolean forFavicon);
void updateSpinnerHandler(WebKitLoadEvent loadEvent, GtkNotebook *tabBar, WebKitWebView *viewport);