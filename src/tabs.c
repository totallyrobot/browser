#include <stdio.h>
#include <gtk/gtk.h>
#include <webkit2/webkit2.h>
#include <glib.h>
#include "paths.h"
#include "main.h"

// now comes the actual tab stuff
typedef struct {
	GtkWidget *tabLabel;
	GtkWidget *closeTabButton;
	GtkWidget *closeTabButtonImage;
	GtkWidget *isAudioPlayingSymbol;
	GtkWidget *favicon;
	GtkWidget *trBrowserTabLabelContainer;
	GtkWidget *spinner;
} TRBrowserTabLabel;

typedef struct {
	WebKitWebView *viewport;
	TRBrowserTabLabel tabLabel;
	WebKitWebContext *tabContext;	
	WebKitWebsiteDataManager *tabWebsiteDataManager;
	WebKitCookieManager *tabCookieManager;
} TRBrowserTab;



TRBrowserTabLabel TRBrowser_TRBrowserTabLabel_new() {
	TRBrowserTabLabel return_value;
	return_value.trBrowserTabLabelContainer = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 6);
	return_value.tabLabel = gtk_label_new("Unnamed Tab");
	return_value.closeTabButton = gtk_button_new();
	return_value.closeTabButtonImage = gtk_image_new();
	return_value.isAudioPlayingSymbol = gtk_image_new();
	return_value.favicon = gtk_image_new();
	return_value.spinner = gtk_spinner_new();
	gtk_spinner_start(GTK_SPINNER(return_value.spinner));
	gtk_image_set_from_icon_name(GTK_IMAGE(return_value.closeTabButtonImage), "window-close", 10);
	gtk_image_set_from_icon_name(GTK_IMAGE(return_value.isAudioPlayingSymbol), "audio-volume-high", 10);
	gtk_container_add(GTK_CONTAINER(return_value.closeTabButton), return_value.closeTabButtonImage);
	gtk_box_pack_start(GTK_BOX(return_value.trBrowserTabLabelContainer), return_value.favicon, FALSE, FALSE, 0);
	// gtk_box_pack_start(GTK_BOX(return_value.trBrowserTabLabelContainer), return_value.isAudioPlayingSymbol, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(return_value.trBrowserTabLabelContainer), return_value.tabLabel, TRUE, FALSE, 0);
	// gtk_box_pack_start(GTK_BOX(return_value.trBrowserTabLabelContainer), return_value.closeTabButton, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(return_value.trBrowserTabLabelContainer), return_value.spinner, FALSE, FALSE, 0);
	gtk_widget_show_all(return_value.trBrowserTabLabelContainer);
	return return_value;
}

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
	g_signal_connect(return_value.viewport, "notify::title", (GCallback) refreshTabLabelEventSignalHandlerNotify, return_value.viewport);
	g_signal_connect(return_value.viewport, "notify::favicon", (GCallback) refreshTabLabelEventSignalHandlerFavicon, return_value.viewport);
	return_value.tabLabel = TRBrowser_TRBrowserTabLabel_new();
	return return_value;
}

TRBrowserTab getCurrentTab(GtkNotebook *tabBar) {
	TRBrowserTab currentTab;
	gint currentTabIndex = gtk_notebook_get_current_page(tabBar);
	currentTab.viewport = WEBKIT_WEB_VIEW(gtk_notebook_get_nth_page(tabBar, currentTabIndex));
	currentTab.tabLabel.trBrowserTabLabelContainer = gtk_notebook_get_tab_label(tabBar, GTK_WIDGET(currentTab.viewport));
	return currentTab;
}

TRBrowserTab getNthTab(gint tabIndex, GtkNotebook *tabBar) {
	TRBrowserTab nthTab;
	nthTab.viewport = WEBKIT_WEB_VIEW(gtk_notebook_get_nth_page(tabBar, tabIndex));
	nthTab.tabLabel.trBrowserTabLabelContainer = gtk_notebook_get_tab_label(tabBar, GTK_WIDGET(nthTab.viewport));
	return nthTab;
}

void refreshTabLabel(guint tabIndex, GtkNotebook *tabBar, gboolean forFavicon, WebKitLoadEvent loadEvent) {
	TRBrowserTab tab = getNthTab(tabIndex, tabBar);
	GList *tabLabelChildrenList = gtk_container_get_children(GTK_CONTAINER(tab.tabLabel.trBrowserTabLabelContainer));
	tab.tabLabel.favicon = g_list_first(tabLabelChildrenList)->data;
	tab.tabLabel.isAudioPlayingSymbol = g_list_first(tabLabelChildrenList)->next->data;
	tab.tabLabel.tabLabel = g_list_first(tabLabelChildrenList)->next->data;
	// tab.tabLabel.closeTabButton = g_list_first(tabLabelChildrenList)->next->next->data;
	tab.tabLabel.spinner = g_list_first(tabLabelChildrenList)->next->next->data;
	gtk_spinner_stop(GTK_SPINNER(tab.tabLabel.spinner));
	// FIXME: get favicons to show up
	if (forFavicon == TRUE)
		gtk_image_set_from_surface(GTK_IMAGE(tab.tabLabel.favicon), webkit_web_view_get_favicon(tab.viewport));
	gtk_label_set_text(GTK_LABEL(tab.tabLabel.tabLabel), webkit_web_view_get_title(tab.viewport));
	gtk_widget_show_all(tab.tabLabel.trBrowserTabLabelContainer);
}