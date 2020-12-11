//
// Created by karaler on 2020/7/22.
// Author: karaler
// Description: 
// Others: 
// Copyright (c) 2020 Bytelang . All rights reserved.
//

#include "KPVideoShowImagePlugin.h"

KPVideoShowImagePlugin::KPVideoShowImagePlugin(const std::string &identify_name, const std::string &filter_name, const KPFilterType &filter_type, PluginParamsObject plugin_params_object) : KPPluginAdapter(identify_name, filter_name, filter_type, std::move(plugin_params_object)) {
    // 赋值described
    std::stringstream filter_desc_stream;

    // 默认值
    std::string x = "0";
    std::string y = "0";

    // 赋值
    if (plugin_params_object.params.find("x") != plugin_params_object.params.end()) {
        x = plugin_params_object.params["x"];
    }
    if (plugin_params_object.params.find("y") != plugin_params_object.params.end()) {
        y = plugin_params_object.params["y"];
    }

    // 参数校验
    if (plugin_params_object.params.find("path") == plugin_params_object.params.end()) {
        logger->warn("插件参数不正确，缺少path参数;");
        throw KPFilterException("插件参数不正确, 缺少path参数");
    }

    std::string       path = plugin_params_object.params["path"];
    KPlayer::FileInfo image_info(path);
    if (!image_info.Exists()) {
        logger->error("初始化插件失败，目标文件不存在; path: {}", path);
        throw KPFilterException("初始化插件失败，目标文件不存在");
    }


    filter_desc_stream << "x=" << x << ":y=" << y;
    filter_desc = filter_desc_stream.str();

    // 查找过滤器
    filter = avfilter_get_by_name("overlay");
    if (filter == nullptr)
        throw KPFilterException("未知过滤器; filter name: overlay");
}

KPVideoShowImagePlugin::~KPVideoShowImagePlugin() {
}

void KPVideoShowImagePlugin::KillTask() {
}

void KPVideoShowImagePlugin::InitTask() {
}

void KPVideoShowImagePlugin::Task() {

}

std::shared_ptr<KPPluginAdapter> KPVideoShowImagePlugin::GetSiblingFilter() {
    return std::shared_ptr<KPShowImagePluginNS::KPOverlayPlugin>(new KPShowImagePluginNS::KPOverlayPlugin("kplayer", "video_plugin_show_image_ns_movie", KP_FILTER_TYPE_VIDEO, plugin_params_object));
}

KPLAYER_PLUGIN_FUNC(KPVideoShowImagePlugin) {
    return new KPVideoShowImagePlugin("kplayer", "video_plugin_show_image", KP_FILTER_TYPE_VIDEO, std::move(plugin_params));
}

KPShowImagePluginNS::KPOverlayPlugin::KPOverlayPlugin(const std::string &identify_name, const std::string &filter_name, const KPFilterType &filter_type, PluginParamsObject plugin_params) : KPPluginAdapter(identify_name, filter_name, filter_type, std::move(plugin_params)) {
    // 赋值described
    std::stringstream filter_desc_stream;

    std::string path = plugin_params_object.params["path"];


    filter_desc_stream << "filename=" << path;
    filter_desc = filter_desc_stream.str();

    // 查找过滤器
    filter = avfilter_get_by_name("movie");
    if (filter == nullptr)
        throw KPFilterException("未知过滤器; filter name: movie");
}

void KPShowImagePluginNS::KPOverlayPlugin::KillTask() {
}

void KPShowImagePluginNS::KPOverlayPlugin::InitTask() {
}

void KPShowImagePluginNS::KPOverlayPlugin::Task() {
}
