#ifndef HEADER_FILE
#define HEADER_FILE
#include <gtk/gtk.h>
#include <webkit2/webkit2.h>

typedef struct {
	WebKitWebView *viewport;
	GtkWidget *tabLabel;
	WebKitWebContext *tabContext;	
	WebKitWebsiteDataManager *tabWebsiteDataManager;
	WebKitCookieManager *tabCookieManager;
} TRBrowserTab;

TRBrowserTab TRBrowser_TRBrowserTab_new();
#endif