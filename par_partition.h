#ifndef PAR_PARTITION_H
#define PAR_PARTITION_H

#include <mpi.h>
#include <vector>

#include "partition.h"


namespace cluster {
  
  /// Parallel partition object.  
  struct par_partition {
    /// Gives the object id for the ith medoid.  This object may not be local.
    std::vector<object_id> medoid_ids;
    
    /// Global cluster ids for local objects.  These are indices into medoid_ids.
    /// The object id of the medoid of the ith local object is medoid_ids[cluster_ids[i]].
    std::vector<object_id> cluster_ids;
    
    /// Communicator, the processes of which this partition divides
    MPI_Comm comm;

    /// Construct a parallel partition for the communicator supplied
    /// Partition starts off with everyone in one cluster with medoid 0.
    par_partition(MPI_Comm comm = MPI_COMM_WORLD);

    /// Virtual destructor for inheritance.
    virtual ~par_partition();

    /// Collective operation.  Gathers my_id from all processes into a 
    /// local partition object. If size of system is large, then this method
    /// will not scale.
    void gather(partition& local, int root=0);
  };
  
} // namespace cluster

#endif // PAR_PARTITION_H


