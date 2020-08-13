//
// Created by karaler on 2020/7/22.
// Author: karaler
// Description: 
// Others: 
// Copyright (c) 2020 Bytelang . All rights reserved.
//

#ifndef KPLAYER_KPVIDEOSHOWIMAGEPLUGIN_H
#define KPLAYER_KPVIDEOSHOWIMAGEPLUGIN_H

#include <utility>

#include "adapter/KPPluginAdapter.h"
#include "util/KPHelper.h"
#include "config.h"

extern "C" {
#include <libavutil/error.h>
}

namespace KPShowImagePluginNS {
    class KPOverlayPlugin : public KPPluginAdapter {
    public:
        KPOverlayPlugin(const std::string &identify_name, const std::string &filter_name, const KPFilterType &filter_type, PluginParams params);
        ~KPOverlayPlugin() override = default;
        void KillTask() override;
        void InitTask() override;
        void Task() override;
    };
};

class KPVideoShowImagePlugin : public KPPluginAdapter {
protected:
    PluginParams params;
public:
    explicit KPVideoShowImagePlugin(const std::string &identify_name, const std::string &filter_name, const KPFilterType &filter_type, PluginParams params);
    ~KPVideoShowImagePlugin() override;
    void KillTask() override;
    void InitTask() override;
    void Task() override;
    std::shared_ptr<KPPluginAdapter> GetSiblingFilter() override;
};

// slot
extern "C" {
KPLAYER_PLUGIN_FUNC(KPVideoShowImagePlugin);
}

#endif //KPLAYER_KPVIDEOSHOWIMAGEPLUGIN_H
