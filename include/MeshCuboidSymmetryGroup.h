/**
* file:	MeshCuboidSymmetryGroup.h
* description:	Define a partial symmetry group of cuboids.
*
* author:	Minhyuk Sung
* date:	March 2015
*/

#ifndef _MESH_CUBOID_SYMMETRY_GROUP_H_
#define _MESH_CUBOID_SYMMETRY_GROUP_H_

#include "MyMesh.h"
#include "MeshCuboid.h"

#include <array>
#include <vector>


struct MeshCuboidSymmetryGroupInfo
{
	MeshCuboidSymmetryGroupInfo(unsigned int _reflection_axis_index);
	MeshCuboidSymmetryGroupInfo(const MeshCuboidSymmetryGroupInfo& _other);

	unsigned int reflection_axis_index_;
	std::vector<LabelIndex> single_label_indices_;
	std::vector< std::pair<LabelIndex, LabelIndex> > pair_label_indices_;
};

class MeshCuboidSymmetryGroup
{
public:
	// NOTICE:
	// Use factory constructor.
	static MeshCuboidSymmetryGroup* constructor(
		const MeshCuboidSymmetryGroupInfo &_info,
		const std::vector<MeshCuboid *>& _cuboids);
	~MeshCuboidSymmetryGroup();


private:
	MeshCuboidSymmetryGroup(const MeshCuboidSymmetryGroupInfo &_info);


public:
	void get_single_cuboid_indices(const std::vector<MeshCuboid *>& _cuboids,
		std::vector<unsigned int> &_single_cuboid_indices) const;

	void get_pair_cuboid_indices(const std::vector<MeshCuboid *>& _cuboids,
		std::vector< std::pair<unsigned int, unsigned int> > &_pair_cuboid_indices) const;

	unsigned int get_reflection_axis_index() const { return info_.reflection_axis_index_; }

	virtual bool compute_symmetry_axis(const std::vector<MeshCuboid *>& _cuboids);

	void get_reflection_plane(MyMesh::Normal &_n, double &_t) const;

	void get_reflection_plane_corners(MyMesh::Point &_point, double _size,
		std::array<MyMesh::Point, 4>& _corners);

	// static functions.
	static void add_symmety_cuboid_corner_points(
		const MeshCuboid *cuboid_1, const MeshCuboid *cuboid_2,
		const std::vector<MeshCuboid *>& _cuboids,
		const unsigned int _reflection_axis_index,
		std::list< std::pair < MyMesh::Point, MyMesh::Point > > &_point_pairs);

	static void compute_reflection_plane(
		const std::list< std::pair < MyMesh::Point, MyMesh::Point > > &_point_pairs,
		MyMesh::Normal &_n, double &_t);


protected:
	const MeshCuboidSymmetryGroupInfo &info_;

	// For any point p on the reflection plane, dot(n, p) = t.
	MyMesh::Normal n_;
	double t_;
};

#endif	// _MESH_CUBOID_SYMMETRY_GROUP_H_