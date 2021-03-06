/*Copyright (c) 2014, School of Computer Science, Fudan University*/
#ifndef FRAMEPROCESSOR_HPP
#define FRAMEPROCESSOR_HPP

#include "FduVideo_lib.hpp"
#include "system_struct.hpp"

class FaceDetection{

    cv::HOGDescriptor hog;
    cv::Mat ROI;
    std::vector<cv::Rect> tmp;
    const options &_ops;

public:

    FaceDetection(const options &ops):
        _ops(ops),
        hog(cv::Size(48,48), cv::Size(16,16), cv::Size(8,8), cv::Size(8,8), 9)
        // set properties
    {
        hog.load(_ops.face_d._hog_head);  // load the classifier
    }

    void processFrame(shared_data &data){
        shared_data::bbox facetmp;
        for(const auto &bbox: data.im_data.im_ROI){
            ROI=data.im_data.image(bbox);
            tmp.clear();
            if(ROI.rows>=48)
                if(ROI.cols>=48)
                    hog.detectMultiScale(ROI, tmp, 1, cv::Size(8,8), cv::Size(0,0), 1.1, 3, false);
            for(cv::Rect &face: tmp){
                face.x+=bbox.x;
                face.y+=bbox.y;
                if(face.height*1.3+face.y<data.im_data.image.rows)
                    face.height=floor(face.height*1.3);              // expand
                facetmp=shared_data::bbox(face);
                facetmp.type_label=TYPE_FACE;                              // means that it's a face
                data.im_boxes.push_back(facetmp);
            }
        }
    }
};



#endif // FRAMEPROCESSOR_HPP
