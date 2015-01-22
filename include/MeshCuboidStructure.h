/**
* file:	MeshCuboidStructure.h
* description:	Define a mesh proxy structure.
*
* author:	Minhyuk Sung
* date:	October 2014
*/

#ifndef _MESH_CUBOID_STRUCTURE_H_
#define _MESH_CUBOID_STRUCTURE_H_

#include "MyMesh.h"
#include "MeshCuboid.h"

#include <vector>
#include <set>


class MeshCuboidStructure {
public:
	MeshCuboidStructure(const MyMesh *_mesh);
	MeshCuboidStructure(const MeshCuboidStructure& _other);	// Copy constructor.
	~MeshCuboidStructure();

	MeshCuboidStructure& operator=(const MeshCuboidStructure& _other);	// Copy assignment.
	void deep_copy(const MeshCuboidStructure& _other);


	void clear();
	void clear_sample_points();
	void clear_cuboids();
	void clear_labels();

	void apply_mesh_transformation();

	inline unsigned int num_sample_points()const {
		return static_cast<unsigned int>(sample_points_.size());
	}

	inline unsigned int num_labels()const {
		return static_cast<unsigned int>(labels_.size());
	}

	Label get_label(const LabelIndex _label_index)const;

	bool exist_label(const Label _label, LabelIndex* _label_index = NULL)const;

	LabelIndex get_label_index(const Label _label)const;

	LabelIndex get_label_index(const std::string _label_name)const;

	bool load_labels(const char *_filename, bool _verbose = true);

	bool load_label_symmetries(const char *_filename, bool _verbose = true);

	bool load_sample_points(const char *_filename, bool _verbose = true);

	bool load_sample_point_labels(const char *_filename, bool _verbose = true);

	std::vector<MeshCuboid *> get_all_cuboids()const;

	void make_mesh_vertices_as_sample_points();

	// Get sample point labels from the label confidence values.
	std::vector<LabelIndex> get_sample_point_label_indices();

	void compute_label_cuboids();

	// Apple mesh face labels to both sample points and parts,
	// but not modify existing parts except their labels.
	void apply_mesh_face_labels_to_cuboids();

	// Apple mesh face labels to sample points,
	// and re-create parts based on sample point labels.
	void get_mesh_face_label_cuboids();

	// Find the largest part for each label.
	void find_the_largest_label_cuboids();

	void split_label_cuboids();

	void print_label_cuboids(const LabelIndex _label_index)const;

	void remove_occluded_sample_points(const std::set<FaceIndex>& _visible_face_indices);

	// Remove cuboids in symmetric labels (when the same cuboids are duplicated for symmetric labels).
	void remove_symmetric_cuboids();

	// TEST.
	bool test_load_cuboids(const char *_filename, bool _verbose = true);

	// Apply labels in new indices.
	//bool set_new_label_indices(const std::vector<Label>& _labels);

	//typedef struct
	//{
	//	bool is_multiple_cuboids_;
	//	std::list<Label> mapped_cuboid_labels_;
	//}
	//PointCuboidLabelMap;

	//bool apply_point_cuboid_label_map(
	//	const std::vector<PointCuboidLabelMap>& _point_cuboid_label_maps,
	//	const std::vector<Label>& _all_cuboid_labels);


private:
	//inline Label get_new_label()const;

	// Apple mesh face labels to sample points
	void apply_mesh_face_labels_to_sample_points();


public:
	const MyMesh *mesh_;

	std::vector<MeshSamplePoint *> sample_points_;
	std::vector<Label> labels_;
	std::vector<std::string> label_names_;
	std::vector< std::list<LabelIndex> > label_symmetries_;
	std::vector< std::vector<MeshCuboid *> > label_cuboids_;

	MyMesh::Normal translation_;
	Real scale_;
	LabelIndex query_label_index_;

	void translate(const MyMesh::Normal _translate);
	void scale(const Real _scale);
	void reset_transformation();
};

#endif	// _MESH_CUBOID_STRUCTURE_H_