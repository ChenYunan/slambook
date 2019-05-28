#include <iostream>
#include <cmath>
using namespace std;

#include <Eigen/Core>
// Eigen 几何模块
#include <Eigen/Geometry>

/****************************
* 本程序演示了 Eigen 几何模块的使用方法
****************************/

int main ( int argc, char** argv )
{
    // Eigen/Geometry 模块提供了各种旋转和平移的表示
    // 3D 旋转矩阵直接使用 Matrix3d 或 Matrix3f
    Eigen::Matrix3d rotation_matrix = Eigen::Matrix3d::Identity();
    // 旋转向量使用 AngleAxis, 它底层不直接是Matrix，但运算可以当作矩阵（因为重载了运算符）
    Eigen::AngleAxisd rotation_vector ( -M_PI/4, Eigen::Vector3d ( 0,0,1 ) );     //沿 Z 轴旋转 45 度////comment by cyn: counter-clockwise?



    Eigen::Matrix3d rotation_Test1, rotation_Test2, rotation_Test3;
    Eigen::AngleAxisd rotation_vector_x ( -M_PI/2, Eigen::Vector3d ( 1,0,0 ) );
    Eigen::AngleAxisd rotation_vector_z ( -M_PI/2, Eigen::Vector3d ( 0,0,1 ) );
    rotation_Test1 = rotation_vector_x.toRotationMatrix();
    cout << "rotation_Test1 is :" << rotation_Test1 << endl;
    rotation_Test2 = rotation_vector_z.toRotationMatrix();
    cout << "rotation_Test2 is :" << rotation_Test2 << endl;
    rotation_Test3 = rotation_Test2 * rotation_Test1;
    cout << "rotation_Test is :" << rotation_Test3 << endl;
    cout << "exchange the sequence of rotation axis:" << rotation_Test1*rotation_Test2 << endl;




    cout<<"rotation matrix =\n"<<rotation_vector.matrix() <<endl;
    //用matrix()转换成矩阵
    // 也可以直接赋值
    rotation_matrix = rotation_vector.toRotationMatrix();
    // 用 AngleAxis 可以进行坐标变换
    Eigen::Vector3d v ( 1,0,0 );
    Eigen::Vector3d v_rotated = rotation_vector * v;
    cout<<"(1,0,0) after rotation = "<<v_rotated.transpose()<<endl;
    // 或者用旋转矩阵
    v_rotated = rotation_matrix * v;
    cout<<"(1,0,0) after rotation = "<<v_rotated.transpose()<<endl;

    // 欧拉角: 可以将旋转矩阵直接转换成欧拉角
    Eigen::Vector3d euler_angles = rotation_matrix.eulerAngles ( 2,1,0 ); // ZYX顺序，即roll pitch yaw顺序
    cout<<"yaw pitch roll = "<<euler_angles.transpose()<<endl;

    // 欧氏变换矩阵使用 Eigen::Isometry
    Eigen::Isometry3d T=Eigen::Isometry3d::Identity();                // 虽然称为3d，实质上是4＊4的矩阵
    T.rotate ( rotation_vector );                                     // 按照rotation_vector进行旋转
    T.pretranslate ( Eigen::Vector3d ( 1,3,4 ) );                     // 把平移向量设成(1,3,4)
    cout << "Transform matrix = \n" << T.matrix() <<endl;

    // 用变换矩阵进行坐标变换
    Eigen::Vector3d v_transformed = T*v;                              // 相当于R*v+t
    cout<<"v tranformed = "<<v_transformed.transpose()<<endl;

    // 对于仿射和射影变换，使用 Eigen::Affine3d 和 Eigen::Projective3d 即可，略

    // 四元数
    // 可以直接把AngleAxis赋值给四元数，反之亦然
    Eigen::Quaterniond q = Eigen::Quaterniond ( rotation_vector );
    cout<<"quaternion = \n"<<q.coeffs() <<endl;   // 请注意coeffs的顺序是(x,y,z,w),w为实部，前三者为虚部
    // 也可以把旋转矩阵赋给它
    q = Eigen::Quaterniond ( rotation_matrix );
    cout<<"quaternion = \n"<<q.coeffs() <<endl;
    // 使用四元数旋转一个向量，使用重载的乘法即可
    v_rotated = q*v; // 注意数学上是qvq^{-1}
    cout<<"(1,0,0) after rotation = "<<v_rotated.transpose()<<endl;

    //test__create_by_cyn
    //Test AngleAxisd is counter-clockwise.
    Eigen::Matrix3d rotation_gc = Eigen::Matrix3d::Identity();
    cout << "rotation_gc before rotation is" << rotation_gc << endl;
    rotation_gc = Eigen::AngleAxisd (0, Eigen::Vector3d::UnitX())
                * Eigen::AngleAxisd (-M_PI/2, Eigen::Vector3d::UnitY())
                * Eigen::AngleAxisd (0, Eigen::Vector3d::UnitZ());
    cout << "rotation_gc after rotation is" << rotation_gc << endl;

/*    Eigen::Quaterniond uavQuaternion (0.999972629581, 0.00739968004621, 6.12306640026e-17, 4.53099724165e-19);
    Eigen::Matrix3d uavRotationMatrix = uavQuaternion.toRotationMatrix();
    Eigen::Vector3d eal = uavRotationMatrix.eulerAngles(2, 1, 0);
    cout << "eal=:" << eal << endl;//

    Eigen::Isometry3d T_iv, T_ivv;
    T_iv.setIdentity();
    T_ivv.setIdentity();
    cout << "T_iv original is:" << T_iv.matrix() << endl;
    Eigen::Matrix3d rotation_matrix11 = Eigen::Matrix3d::Identity();
    Eigen::Matrix3d rotation_test;
    rotation_test << 1, 2, 3, 4, 5, 6, 7, 8, 9;
    T_ivv.prerotate(rotation_test);
    cout << "T_ivv prerotate is:" << T_ivv.matrix() << endl;
    T_iv.matrix().block(0, 0, 3, 3) = rotation_matrix11;
    T_iv.pretranslate( Eigen::Vector3d(3, 3, 3));
    cout << "T_iv is:" << T_iv.matrix() << endl;*/

    //So, the test result is T.prerotate() and T.pretranslate() can be set the block value of rotation matrix and translation vector.


    return 0;
}
