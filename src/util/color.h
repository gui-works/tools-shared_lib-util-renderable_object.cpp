/*=====================================================================================
  color.h
Description:  Color class

Created by Chen Chen on 09/28/2015
=====================================================================================*/

#ifndef COLOR_
#define COLOR_

#include "headers.h"

class Color {

    public:

        Color();
        Color(float r, float g, float b, float a);
        Color(float r, float g, float b);
        Color(int r, int g, int b);
        Color(int r, int g, int b, int a);
        Color(const Color &c);
        Color(const float *c);
        ~Color();

        void set(float r, float g, float b, float a);

        Color &get();
        float *getArray();

        void getRGBA(float &r, float &g, float &b, float &a);
        void getRGBA(int &r, int &g, int &b, int &a);

        void print();
        void clamp();
        float luminance();
        void invert();
        Color inverted();

        // Static Functions
        static glm::vec4 getDiscreteColor(int idx);
        static glm::vec4 getContinuousColor(float value, float low = 0.0f, float hight = 1.0f, bool interpolate = false);
        static glm::vec4 getJetColor(float value);

        //Assignment
        Color &operator =  (const Color &c);
        Color &operator += (const Color &c);
        Color &operator += (float s);
        Color &operator -= (const Color &c);
        Color &operator -= (float s);
        Color &operator *= (const Color &c);
        Color &operator *= (float s);    
        Color &operator /= (const Color &c);
        Color &operator /= (float s);

        //Arithmetic
        Color operator + (const Color &c) const;
        Color operator + (float s) const;	
        Color operator - (const Color &c) const;
        Color operator - (float s) const;
        Color operator - () const;
        Color operator * (const Color &c) const;
        Color operator * (float s) const;
        Color operator / (const Color &c) const;
        Color operator / (float s) const;

        //Comparison
        bool operator == (const Color &c);
        bool operator != (const Color &c);
        bool operator <= (const Color &c);
        bool operator <  (const Color &c);
        bool operator >= (const Color &c);
        bool operator >  (const Color &c);	

        float r;
        float g;
        float b; 
        float a;

        float color[4];

};

#endif /* end of include guard: COLOR_ */
