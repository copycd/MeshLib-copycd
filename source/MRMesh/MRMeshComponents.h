#pragma once

#include "MRUnionFind.h"
#include <functional>

namespace MR
{

namespace MeshComponents
{

/// \defgroup MeshComponentsGroup MeshComponents
/// \ingroup ComponentsGroup
/// \{

/// Face incidence type
enum FaceIncidence
{
    PerEdge, ///< face can have neighbor only via edge
    PerVertex ///< face can have neighbor via vertex
};

/// returns one connected component containing given face, 
/// not effective to call more than once, if several components are needed use getAllComponents
[[nodiscard]] MRMESH_API FaceBitSet getComponent( const MeshPart& meshPart, FaceId id, FaceIncidence incidence = FaceIncidence::PerEdge );
/// returns one connected component containing given vertex, 
/// not effective to call more than once, if several components are needed use getAllComponentsVerts
[[nodiscard]] MRMESH_API VertBitSet getComponentVerts( const Mesh& mesh, VertId id, const VertBitSet* region = nullptr );

/// returns largest by surface area component
[[nodiscard]] MRMESH_API FaceBitSet getLargestComponent( const MeshPart& meshPart, FaceIncidence incidence = FaceIncidence::PerEdge );
/// returns largest by number of elements component
[[nodiscard]] MRMESH_API VertBitSet getLargestComponentVerts( const Mesh& mesh, const VertBitSet* region = nullptr );

/// returns union of connected components, each of which contains at least one seed face
[[nodiscard]] MRMESH_API FaceBitSet getComponents( const MeshPart& meshPart, const FaceBitSet & seeds, FaceIncidence incidence = FaceIncidence::PerEdge );
/// returns the union of connected components, each having at least given area
[[nodiscard]] MRMESH_API FaceBitSet getLargeByAreaComponents( const MeshPart& meshPart, float minArea );
/// given prepared union-find structure returns the union of connected components, each having at least given area
[[nodiscard]] MRMESH_API FaceBitSet getLargeByAreaComponents( const MeshPart& meshPart, UnionFind<FaceId> & unionFind, float minArea,
    UndirectedEdgeBitSet * bdEdgesBetweenLargeComps = nullptr );
/// returns the union of connected components, each having at least given area,
/// and any two faces in a connected component have a path along the surface across the edges, where surface does not deviate from plane more than on given angle
[[nodiscard]] MRMESH_API FaceBitSet getLargeByAreaSmoothComponents( const MeshPart& meshPart, float minArea, float angleFromPlanar,
    UndirectedEdgeBitSet * bdEdgesBetweenLargeComps = nullptr );
/// returns union of connected components, each of which contains at least one seed vert
[[nodiscard]] MRMESH_API VertBitSet getComponentsVerts( const Mesh& mesh, const VertBitSet& seeds, const VertBitSet* region = nullptr );

/// returns the number of connected components in mesh part
[[nodiscard]] MRMESH_API size_t getNumComponents( const MeshPart& meshPart, FaceIncidence incidence = FaceIncidence::PerEdge );

/// gets all connected components of mesh part
[[nodiscard]] MRMESH_API std::vector<FaceBitSet> getAllComponents( const MeshPart& meshPart, FaceIncidence incidence = FaceIncidence::PerEdge );
[[nodiscard]] MRMESH_API std::vector<VertBitSet> getAllComponentsVerts( const Mesh& mesh, const VertBitSet* region = nullptr );
/// gets all connected components, separating vertices by given path (either closed or from boundary to boundary)
[[nodiscard]] MRMESH_API std::vector<VertBitSet> getAllComponentsVertsSeparatedByPath( const Mesh& mesh, const SurfacePath& path );
/// subdivides given edges on connected components
[[nodiscard]] MRMESH_API std::vector<EdgeBitSet> getAllComponentsEdges( const Mesh& mesh, const EdgeBitSet & edges );

/// returns true if all vertices of a mesh connected component are present in selection
[[nodiscard]] MRMESH_API bool hasFullySelectedComponent( const Mesh& mesh, const VertBitSet & selection );

/// gets union-find structure for faces with different options of face-connectivity
[[nodiscard]] MRMESH_API UnionFind<FaceId> getUnionFindStructureFaces( const MeshPart& meshPart, FaceIncidence incidence = FaceIncidence::PerEdge );
/// gets union-find structure for faces with connectivity by shared edge, and optional edge predicate whether to unite components over it
[[nodiscard]] MRMESH_API UnionFind<FaceId> getUnionFindStructureFacesPerEdge( const MeshPart& meshPart, std::function<bool(UndirectedEdgeId)> uniteOverEdge = {} );
/// gets union-find structure for vertices
[[nodiscard]] MRMESH_API UnionFind<VertId> getUnionFindStructureVerts( const Mesh& mesh, const VertBitSet* region = nullptr );
/// gets union-find structure for vertices, considering connections by given edges only
[[nodiscard]] MRMESH_API UnionFind<VertId> getUnionFindStructureVerts( const Mesh& mesh, const EdgeBitSet & edges );
/// gets union-find structure for vertices, considering connections by all edges excluding given ones
[[nodiscard]] MRMESH_API UnionFind<VertId> getUnionFindStructureVertsEx( const Mesh& mesh, const UndirectedEdgeBitSet & ignoreEdges );
/**
 * \brief gets union-find structure for vertices, separating vertices by given path (either closed or from boundary to boundary)
 * \param outPathVerts this set receives all vertices passed by the path
 */
[[nodiscard]] MRMESH_API UnionFind<VertId> getUnionFindStructureVertsSeparatedByPath( const Mesh& mesh, const SurfacePath& path, 
    VertBitSet * outPathVerts = nullptr );

// \}

} // namespace MeshComponents

} // namespace MR
