//
//  TrackerInterface.cpp
//  FVAS
//
//  Created by 陈裕昕 on 10/31/14.
//  Copyright (c) 2014 Fudan. All rights reserved.
//

#include "TrackerInterface.h"

void TrackerInterface::track(shared_data &in_data)
{
    if(!have_pre) return;
    
    Mat &prevImg = pre_data.im_data.image, &nextImg = in_data.im_data.image;
    
    for(auto box:pre_data.im_boxes)
    {
        if(box.type_label == TYPE_TRACK)
        {
            MedianFlow &medianFlow = *(new MedianFlow(prevImg, nextImg));
            int status;
            Rect_<float> retBox = medianFlow.trackBox(box, status);
            
            if(status == MedianFlow::MEDIANFLOW_TRACK_SUCCESS)
            {
                Rect_<int> retBoxInt(retBox.tl(), retBox.br());
                shared_data::bbox temp_box(retBoxInt);
                temp_box.type_label = TYPE_TRACK;
                temp_box.prob = box.prob;
                temp_box.result_label = box.result_label;
                in_data.im_boxes.push_back(temp_box);
            }
            delete &medianFlow;
        }
    }
    

}