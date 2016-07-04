#ifndef _F2D_MACROS_H_H_
#define _F2D_MACROS_H_H_

#define NS_F2D_BEGIN namespace Frame2D {
#define NS_F2D_END }
#define USING_NS_F2D using namespace Frame2D;

#define __DLL __declspec(dllexport)

#define CALLBACK_PARAMETER_0(__selector__,__target__, ...) std::bind(&__selector__,__target__, ##__VA_ARGS__)
#define CALLBACK_PARAMETER_1(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, ##__VA_ARGS__)
#define CALLBACK_PARAMETER_2(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, std::placeholders::_2, ##__VA_ARGS__)
#define CALLBACK_PARAMETER_3(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, ##__VA_ARGS__)
#define CALLBACK_PARAMETER_4(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, ##__VA_ARGS__)

#endif