//
//  TrackerInterface.h
//  FVAS
//
//  Created by 陈裕昕 on 10/31/14.
//  Copyright (c) 2014 Fudan. All rights reserved.
//

#ifndef __FVAS__TrackerInterface__
#define __FVAS__TrackerInterface__

#include "system_struct.hpp"
#include "MedianFlow.h"

class TrackerInterface
{
private:
    
public:
    class track_data
    {
    public:
        shared_data::frame im_data;
        shared_data::info im_info;
        std::vector<shared_data::bbox> im_boxes;
        track_data& operator =(const track_data& t)
        {
            cv::Mat temp=t.im_data.image.clone();
            std::swap(temp, im_data.image);
            im_data.im_ROI=t.im_data.im_ROI;
            im_boxes.clear();
            for (auto i:t.im_boxes)
                im_boxes.push_back(i);
            im_info=t.im_info;
            return *this;
        }
        track_data& operator =(const shared_data& t)
        {
            cv::Mat temp=t.im_data.image.clone();
            std::swap(temp, im_data.image);
            im_boxes.clear();
            for (auto i:t.im_boxes)
                im_boxes.push_back(i);
            im_info=t.im_info;
            return *this;
        }
    };
    
    track_data pre_data;
    bool have_pre{false};
    options::opt_track opt;
    TrackerInterface(options in_opt):
    opt(in_opt.track)
    {}
    void track_push(shared_data &in_data)
    {
        have_pre=true;
        pre_data=in_data;
    }
    
    TrackerInterface(){}
    
    ~TrackerInterface(){}
    
    void track(shared_data &data);
};

#endif /* defined(__FVAS__TrackerInterface__) */
