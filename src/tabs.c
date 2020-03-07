#include <stdio.h>
#include <gtk/gtk.h>
#include <webkit2/webkit2.h>
#include <glib.h>
#include "paths.h"
#include "main.h"

// now comes the actual tab stuff
typedef struct {
	WebKitWebView *viewport;
	GtkWidget *tabLabel;
	WebKitWebContext *tabContext;	
	WebKitWebsiteDataManager *tabWebsiteDataManager;
	WebKitCookieManager *tabCookieManager;
} TRBrowserTab;

TRBrowserTab TRBrowser_TRBrowserTab_new() {
	TRBrowserTab return_value;
	char destDataBaseDir[200] = "";
	char destCacheBaseDir[200] = "";

	return_value.tabWebsiteDataManager = webkit_website_data_manager_new(
		"base-data-directory", getDataBaseDir(destDataBaseDir),
		"base-cache-directory", getCacheBaseDir(destCacheBaseDir),
		NULL
	);
	return_value.tabContext = webkit_web_context_new_with_website_data_manager(return_value.tabWebsiteDataManager);
	return_value.tabCookieManager = webkit_web_context_get_cookie_manager(return_value.tabContext);
	webkit_cookie_manager_set_persistent_storage(
		return_value.tabCookieManager,
		"/home/maxi/.browser/cookies.txt",
		WEBKIT_COOKIE_PERSISTENT_STORAGE_TEXT
	);
	webkit_cookie_manager_set_accept_policy(
		return_value.tabCookieManager,
		WEBKIT_COOKIE_POLICY_ACCEPT_NO_THIRD_PARTY
	);

	return_value.viewport = WEBKIT_WEB_VIEW(webkit_web_view_new_with_context(return_value.tabContext));
	g_signal_connect(return_value.viewport, "load-changed", (GCallback) refreshCurrentTabUrlBarSignalHandler, NULL);
	return_value.tabLabel = GTK_WIDGET(gtk_label_new("test"));
	return return_value;
}

TRBrowserTab getCurrentTab(GtkNotebook *tabBar) {
	TRBrowserTab currentTab;
	gint currentTabIndex = gtk_notebook_get_current_page(tabBar);
	currentTab.viewport = WEBKIT_WEB_VIEW(gtk_notebook_get_nth_page(tabBar, currentTabIndex));
	currentTab.tabLabel = gtk_notebook_get_tab_label(tabBar, GTK_WIDGET(currentTab.viewport));
	return currentTab;
}

TRBrowserTab getNthTab(gint tabIndex, GtkNotebook *tabBar) {
	TRBrowserTab nthTab;
	nthTab.viewport = WEBKIT_WEB_VIEW(gtk_notebook_get_nth_page(tabBar, tabIndex));
	nthTab.tabLabel = gtk_notebook_get_tab_label(tabBar, GTK_WIDGET(nthTab.viewport));
	return nthTab;
}