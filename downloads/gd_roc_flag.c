#include <gd.h>
#include <math.h>

void draw_exam_flag(gdImagePtr img);
void draw_white_sun(gdImagePtr img, int center_x, int center_y, int sun_radius, int white, int red, int blue);

int main() {
    // width 3: height 2
    int width = 1200;
    int height = (int)(width*2.0 / 3.0);

    gdImagePtr img = gdImageCreateTrueColor(width, height);
    gdImageAlphaBlending(img, 0);

    draw_exam_flag(img);

    FILE *outputFile = fopen("./exam_flag.png", "wb");
    if (outputFile == NULL) {
        fprintf(stderr, "Error opening the output file.\n");
        return 1;
    }
    gdImagePngEx(img, outputFile, 9);
    fclose(outputFile);
    gdImageDestroy(img);
    return 0;
}

void draw_exam_flag(gdImagePtr img) {
    int width = gdImageSX(img);
    int height = gdImageSY(img);
    int red, white, blue;
    int center_x = (int)(width/4);
    int center_y = (int)(height/4);
    int sun_radius = (int)(width/8);
    int lineColor = gdImageColorAllocate(img, 255, 255, 255);

  // 畫一條線
    int x1 = 429;
    int y1 = 125;
    int x2 = 170;
    int y2 = 274;

    int x3 = 279;
    int y3 = 165;
    int x4 = 170;
    int y4 = 274;

    int x5 = 279;
    int y5 = 165;
    int x6 = 429;
    int y6 = 125;

    // Colors for the flag
    red = gdImageColorAllocate(img, 242, 0, 0); // Red color
    white = gdImageColorAllocate(img, 255, 255, 255); // White stripes
    blue = gdImageColorAllocate(img, 0, 41, 204); // Blue

    // 繪製紅色矩形區域
    gdImageFilledRectangle(img, 0, 0, width, height, red);

    // 繪製藍色矩形區域
    gdImageFilledRectangle(img, 0, 0, (int)(width/2.0), (int)(height/2.0), blue);

    gdImageLine(img, x1, y1, x2, y2, lineColor);

    gdImageLine(img, x3, y3, x4, y4, lineColor);

    gdImageLine(img, x5, y5, x6, y6, lineColor);

    return 0;
}


找交點程式

1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
26
27
28
29
30
31
32
33
34
35
36
37
38
39
40
41
42
43
44
45
46
47
48
49
50
51
52
53
54
55
56
57
58
59
60
61
62
63
64
65
66
67
68
69
70
71
72
73
74
75
76
77
78
79
80
81
82
83
84
85
86
87
88
89
90
91
92
93
94
95
96
97
98
99
100
101
102
103
104
105
106
107
108
109
110
111
112
113
114
115
116
117
118
119
120
121
122
123
124
125
126
127
128
129
130
131
132
133
134
135
136
137
138
139
140
141
142
143
144
145
146
147
148
149
150
151
152
153
154
155
156
157
158
159
160
161
162
163
164
165
166
167
168
169
170
171
172
173
174
175
176
177
178
179
180
181
182
183
184
185
186
187
188
189
190
191
192
193
194
195
196
197
198
199
200
201
202
203
204
205
206
207
208
209
210
211
212
213
214
215
216
217
218
219
220
221
222
223
224
225
226
227
228
229
230
231
232
233
234
235
236
237
238
239
240
241
242
243
244
245
246
247
248
249
250
251
252
253
254
255
256
257
258
259
260
261
262
263
264
265
266
267
268
269
270
271
272
273
274
275
276
277
278
279
280
281
282
283
284
285
286
287
288
289
290
291
292
293
294
295
296
297
298
299
300
301
302
303
304
305
#include <stdio.h>

#include <gd.h>

#include <math.h>



void draw_roc_flag(gdImagePtr img);

void draw_white_sun(gdImagePtr img, int x, int y, int size, int color);



int main() {

    // width 3: height 2

    int width = 1200;

    // 國旗長寬比為 3:2

    int height = (int)(width*2.0 / 3.0);



    gdImagePtr img = gdImageCreateTrueColor(width, height);

    gdImageAlphaBlending(img, 0);



    draw_roc_flag(img);



    FILE *outputFile = fopen("roc_flag_in_gd.png", "wb");

    if (outputFile == NULL) {

        fprintf(stderr, "Error opening the output file.\n");

        return 1;

    }

    gdImagePngEx(img, outputFile, 9);

    fclose(outputFile);

    gdImageDestroy(img);

    return 0;

}



void draw_roc_flag(gdImagePtr img) {

    int width = gdImageSX(img);

    int height = gdImageSY(img);

    int red, white, blue;

    // 白日位於青天面積正中央, 因此中心點座標為長寬各 1/4 處

    int center_x = (int)(width/4);

    int center_y = (int)(height/4);

    // gdImageFilledEllipse 需以長寬方向的 diameter 作圖

    // 由於中央白日圓形的半徑為青天寬度的 1/8

    // 因此中央白日圓形的直徑為青天寬度的 1/4, 也就是國旗寬度的 1/8

    // 而且白日十二道光芒的外圍圓形其半徑也是國旗寬度的1/8

    int sun_radius = (int)(width/8);

    // 中央白日圓形的直徑等於十二道光芒外圍圓形的半徑

    int white_circle_dia = sun_radius;

    // 中央藍色圓形半徑為中央白日的 1又 2/15

    int blue_circle_dia = white_circle_dia +  white_circle_dia*2/15;

    // 根據 https://www.moi.gov.tw/cp.aspx?n=10621 訂定國旗三種顏色值

    red = gdImageColorAllocate(img, 255, 0, 0); // 紅色

    white = gdImageColorAllocate(img, 255, 255, 255); // 白色

    blue = gdImageColorAllocate(img, 0, 0, 149); // 藍色

    // 根據畫布大小塗上紅色長方形區域

    gdImageFilledRectangle(img, 0, 0, width, height, red);

    // 青天面積為整面國旗的 1/4, 也是採用長方形塗色

    gdImageFilledRectangle(img, 0, 0, (int)(width/2.0), (int)(height/2.0), blue);

  {int x1 = 429;

   int y1 = 125;

   int x2 = 279;

   int y2 = 165;



   // 畫一條線連接兩個點

   gdImageLine(img, x1, y1, x2, y2, white);

  }

  {int x1 = 170;

     int y1 = 274;

     int x2 = 279;

     int y2 = 165;



     // 畫一條線連接兩個點

     gdImageLine(img, x1, y1, x2, y2, white);

  }

  {

    int x1 = 170;

     int y1 = 274;

     int x2 = 429;

     int y2 = 125;



     // 畫一條線連接兩個點

     gdImageLine(img, x1, y1, x2, y2, white);

  }

  // 利用一個藍色大圓與白色小圓畫出藍色環狀

  gdImageFilledEllipse(img, center_x, center_y, blue_circle_dia, blue_circle_dia, blue);

  gdImageFilledEllipse(img, center_x, center_y, white_circle_dia, white_circle_dia, white);





  // 定義座標結構

  typedef struct {

      double x;

      double y;

  } Point;



  // 計算圓與線的交點

  void circleLineIntersection(double h, double k, double r, double x1, double y1, double x2, double y2) {

      // 直線斜率

      double m = (y2 - y1) / (x2 - x1);



      // 直線方程式中的常數項

      double b = y1 - m * x1;



      // 圓與直線交點的計算

      double A = 1 + pow(m, 2);

      double B = 2 * (m * b - m * k - h);

      double C = pow(k, 2) - pow(r, 2) + pow(h, 2) - 2 * b * k + pow(b, 2);



      // 判斷交點個數

    double discriminant = pow(B, 2) - 4 * A * C;

    if (discriminant > 0) {

        double x_intersect1 = (-B + sqrt(discriminant)) / (2 * A);

        double y_intersect1 = m * x_intersect1 + b;

        printf("交點: (%.2f, %.2f)\n", x_intersect1, y_intersect1);



        double x_intersect2 = (-B - sqrt(discriminant)) / (2 * A);

        double y_intersect2 = m * x_intersect2 + b;

        printf("交點: (%.2f, %.2f)\n", x_intersect2, y_intersect2);

    } else if (discriminant == 0) {

        double x_intersect = -B / (2 * A);

        double y_intersect = m * x_intersect + b;

        printf("交點: (%.2f, %.2f)\n", x_intersect, y_intersect);

    } else {

        printf("No points.\n");

    }



  }





      // 圓的參數

      double circle_x = (int)(width/4); // 圓心 x 座標

      double circle_y = (int)(height/4); // 圓心 y 座標

      double radius = white_circle_dia +  white_circle_dia*2/15;   // 圓半徑



      // 兩點座標







  double x3 = 170;

  double y3 = 274;

  double x4 = 279;

  double y4 = 165;



  circleLineIntersection(circle_x, circle_y, radius, x4, y4, x3, y3);





  double x5 = 279;

  double y5 = 165;

  double x6 = 429;

  double y6 = 125;



  circleLineIntersection(circle_x, circle_y, radius, x6, y6, x5, y5);













  }