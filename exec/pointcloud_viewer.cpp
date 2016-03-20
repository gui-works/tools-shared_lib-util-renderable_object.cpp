#include <iostream>

#include <pcl/io/pcd_io.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include "viewer.h"

int main(int argc, char** argv) {
    if (argc < 3) {
        cout << "ERROR usage: \n\tCorrect usage is: ./pointcloud_viewer "
                "pointcloud1.pcd pointcloud2.pcd"
             << endl;
        return 0;
    }

    pcl::PointCloud<pcl::PointXYZI>::Ptr cloud(
        new pcl::PointCloud<pcl::PointXYZI>);
    // Load pointcloud
    if (pcl::io::loadPCDFile<pcl::PointXYZI>(argv[1], *cloud) == -1) {
        PCL_ERROR("Couldn't read file test_pcd.pcd \n");
        return (-1);
    }

    pcl::PointCloud<pcl::PointXYZI>::Ptr cloud1(
        new pcl::PointCloud<pcl::PointXYZI>);
    // Load pointcloud
    if (pcl::io::loadPCDFile<pcl::PointXYZI>(argv[2], *cloud1) == -1) {
        PCL_ERROR("Couldn't read file test_pcd.pcd \n");
        return (-1);
    }

    cout << "point cloud loaded, there are " << cloud->size() << " points."
         << endl;
    cout << "point cloud loaded, there are " << cloud1->size() << " points."
         << endl;

    Viewer pointcloud_viewer;
    pointcloud_viewer.addPointCloud(cloud, glm::vec4(1.0f, 0.0f, 0.0f, 0.7f));
    pointcloud_viewer.addPointCloud(cloud1, glm::vec4(0.0f, 1.0f, 0.0f, 0.7f));

    pointcloud_viewer.draw();

    return 0;
}
