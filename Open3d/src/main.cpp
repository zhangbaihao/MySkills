#include <string>

#include "Open3D/Open3D.h"

int main()
{
    auto cloud_ptr = std::make_shared<open3d::geometry::PointCloud>();
    if (!open3d::io::ReadPointCloud("./cloud.pcd", *cloud_ptr))
    {
        return -1;
    }

    // auto mesh_ptr = std::make_shared<open3d::geometry::TriangleMesh>();
    // if (!open3d::io::ReadTriangleMesh("./mesh.stl", *mesh_ptr)) { return -1; }

    // for (int i = 0; i < mesh_ptr->vertex_normals_.size(); i++) {
    //	std::cout << "i:" << i;
    //	std::cout << " 0:" << mesh_ptr->vertex_normals_[i][0];
    //	std::cout << " 1:" << mesh_ptr->vertex_normals_[i][1];
    //	std::cout << " 2:" << mesh_ptr->vertex_normals_[i][2];
    //	std::cout << std::endl;
    // }
    // 修改MESH中的颜色
    // Eigen::Vector3d color(0,0,0);
    // for (int i = 0; i < mesh_ptr->vertices_.size(); i++) {
    //	mesh_ptr->vertex_colors_.push_back(color);
    // }

    // open3d::visualization::DrawGeometries({ mesh_ptr });
    if (0)
    {

        open3d::visualization::Visualizer visualizer;                          // 创建一个可视化对象
        visualizer.CreateVisualizerWindow("open3d", 1280, 1024, 50, 50, true); // 创建一个窗口

        Eigen::Vector3d backcolo(0, 0, 0);
        visualizer.GetRenderOption().background_color_ = backcolo; // 设置窗口背景色
        visualizer.GetRenderOption().show_coordinate_frame_ = true;
        visualizer.AddGeometry(cloud_ptr); // 把点云add进去,只add一次,不然显示出来视角不能转

        visualizer.UpdateGeometry(cloud_ptr); // MESH数据更新时，需要调用更新显示

        while (1)
        {
            visualizer.PollEvents(); // 下头这两个不清楚啥用
            // visualizer.UpdateRender();
            // Sleep(100);
        }
    }
    else
    {
        open3d::visualization::DrawGeometriesWithEditing({ cloud_ptr }, "Editing", 1920, 1080);

        // open3d::visualization::VisualizerWithEditing visualizer;
        // if (visualizer.CreateVisualizerWindow("open3d", 1920, 1080, 50, 50))
        // {
        //     // MESH数据更新时，需要调用更新显示
        //     if (visualizer.AddGeometry(cloud_ptr))
        //     {
        //         visualizer.UpdateGeometry(cloud_ptr);
        //     }
        // }
        // visualizer.UpdateRender();
        // while (1)
        // {
            
        //     visualizer.PollEvents();
        //     std::this_thread::sleep_for(std::chrono::milliseconds(100));
        // }
    }
    return 0;
}