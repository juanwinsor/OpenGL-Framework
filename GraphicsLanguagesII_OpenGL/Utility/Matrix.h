#ifndef __Matrix_H__
#define __Matrix_H__

class Matrix
{
public:
    float m11, m12, m13, m14, m21, m22, m23, m24, m31, m32, m33, m34, m41, m42, m43, m44;

public:
    Matrix() {}
	Matrix(const Vector3& right, const Vector3& up, const Vector3& at)
    : m11(right.x), m12(up.x), m13(at.x), m14(0)
    , m21(right.y), m22(up.y), m23(at.y), m24(0)
    , m31(right.z), m32(up.z), m33(at.z), m34(0)
    , m41(0),       m42(0),    m43(0),    m44(1) {}

    void SetIdentity();
    void SetPosition(Vector3 pos);
    void SetPosition(float x, float y, float z);
    void SetFrustum(float left, float right, float bottom, float top, float nearZ, float farZ);
    void SetPerspective(float fovy, float aspect, float nearZ, float farZ);
    void SetOrtho(float left, float right, float bottom, float top, float nearZ, float farZ);
	void SetLookAtLH(const Vector3& eye, const Vector3& up, const Vector3& at);
	void SetLookAtRH(const Vector3& eye, const Vector3& up, const Vector3& at);

    void Multiply(Matrix* src);

    void Scale(float sx, float sy, float sz);
    void TranslatePreRotation(float tx, float ty, float tz);
    void TranslatePostRotation(float tx, float ty, float tz);
    void Rotate(float angle, float x, float y, float z);
};

#endif //__Matrix_H__
