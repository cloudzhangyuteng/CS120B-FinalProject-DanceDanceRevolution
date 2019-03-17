#ifndef _note_h__
#define _note_h__

#define Cb3 123.47		// .1
#define Db3 138.59		// .2
#define Eb3 155.56		// .3

#define F3 174.61		// .4

#define Gb3 185.00		// .5
#define Ab3 207.65		// .6
#define Bb3 233.88		// .7


#define Cb4 246.94		// 1
#define D4  293.66
#define Db4 277.18		// 2
#define Eb4 311.13		// 3

#define F4 349.23		// 4

#define Gb4 369.99		// 5
#define Ab4 415.30		// 6
#define Bb4 466.16		// 7


#define Cb5 493.88		// 1.
#define Db5 554.36		// 2.
#define Eb5 622.26		// 3.

#define F5 698.46		// 4.

#define Gb5 739.99		// 5.
#define Ab5 830.61		// 6.
#define Bb5 932.33		// 7.

// 3 4 5 6 7 - 3. 2.
const double song[32] = 
{
	Eb4, F4, Gb4, Ab4, Bb4, 0, Eb5, Db5, 
	Bb4, 0, Eb4, 0, Bb4, Ab4, Gb4, F4, 
	Eb4, F4, Gb4, Ab4, Bb4, 0, Ab4, Gb4, 
	F4, Eb4, F4, Gb4, F4, Eb4, D4, F4
};

#endif