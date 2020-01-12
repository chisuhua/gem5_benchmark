#pragma once
#include "dmr.h"

void write_mesh(std::string infile, ShMesh &mesh, std::string outdir = "")
{
    FORD *nodex, *nodey;

    nodex = mesh.nodex.cpu_rd_ptr();
    nodey = mesh.nodey.cpu_rd_ptr();

    if (outdir.length() > 0) {
        unsigned slash = outdir.rfind("/");
        if (slash != outdir.length() - 1) {
            outdir = outdir + "/";
        }
    }

    unsigned slash = infile.rfind("/");
    std::string outfilehead = outdir + infile.substr(slash + 1);
    std::cout << "  -- " << outfilehead + ".out.node (" << mesh.nnodes << " nodes)" << std::endl;
    std::ofstream outfilenode((outfilehead + ".out.node").c_str());
    outfilenode.precision(17);
    outfilenode << mesh.nnodes << " 2 0 0\n";
    for (unsigned ii = 0; ii < mesh.nnodes; ++ii) {
        outfilenode << ii << " " << nodex[ii] << " " << nodey[ii] << "\n";
    }
    outfilenode.close();

    uint3 *elements = mesh.elements.cpu_rd_ptr();
    bool *isdel = mesh.isdel.cpu_rd_ptr();

    unsigned ntriangles2 = mesh.nelements;
    unsigned segmentcnt = 0;
    for (unsigned ii = 0; ii < mesh.nelements; ++ii) {
        if (IS_SEGMENT(elements[ii]) || isdel[ii])
            ntriangles2--;
        if (IS_SEGMENT(elements[ii]) && !isdel[ii])
            segmentcnt++;
    }

    std::cout << "  -- " << outfilehead + ".out.ele (" << ntriangles2 << " triangles)" << std::endl;
    std::ofstream outfileele((outfilehead + ".out.ele").c_str());

    outfileele << ntriangles2 << " 3 0\n";
    unsigned kk = 0;
    for (unsigned ii = 0; ii < mesh.nelements; ++ii) {
        if (!IS_SEGMENT(elements[ii]) && !isdel[ii])
            outfileele << kk++ << " " << elements[ii].x << " " << elements[ii].y << " " << elements[ii].z << "\n";
    }
    outfileele.close();

    std::cout << "  -- " << outfilehead + ".out.poly (" << segmentcnt << " segments)" << std::endl;
    std::ofstream outfilepoly((outfilehead + ".out.poly").c_str());
    outfilepoly << "0 2 0 1\n";
    outfilepoly << segmentcnt << " 0\n";
    kk = 0;
    for (unsigned ii = 0; ii < mesh.nelements; ++ii) {
        if (IS_SEGMENT(elements[ii]) && !isdel[ii])
            outfilepoly << kk++ << " " << elements[ii].x << " " << elements[ii].y << "\n";
    }
    outfilepoly << "0\n";
    outfilepoly.close();

    std::cout << (ntriangles2 + segmentcnt) << " active elements of " << mesh.nelements << " total elements (" << mesh.nelements / (ntriangles2 + segmentcnt) << "x) " << std::endl;
    std::cout << 1.0 * mesh.maxnelements / mesh.nelements << " ratio of used to free elements." << std::endl;
}

void next_line(std::ifstream& scanner)
{
    scanner.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void readNodes(std::string filename, ShMesh &mesh, int maxfactor = 2)
{
    unsigned index;
    FORD x, y;
    bool firstindex = true;

    std::ifstream scanner(filename.append(".node").c_str());
    scanner >> mesh.nnodes;

    mesh.maxnnodes = (maxfactor /  MAX_NNODES_TO_NELEMENTS) * mesh.nnodes;
    printf("memory for nodes: %lu MB\n", mesh.maxnnodes * sizeof(FORD) * 2 / 1048576);
    mesh.nodex = Shared<FORD> (mesh.maxnnodes);
    mesh.nodey = Shared<FORD> (mesh.maxnnodes);

    FORD *nodex = mesh.nodex.cpu_wr_ptr(true);
    FORD *nodey = mesh.nodey.cpu_wr_ptr(true);

    for (unsigned i = 0; i < mesh.nnodes; i++) {
        next_line(scanner);
        scanner >> index >> x >> y;
        if (firstindex) {
            assert(index == 0);
            firstindex = false;
        }

        nodex[index] = x;
        nodey[index] = y;
    }
}

void readTriangles(std::string basename, ShMesh &mesh, int maxfactor = 2)
{
    unsigned ntriangles, nsegments;
    unsigned i, index, n1, n2, n3;
    bool firstindex = true;
    std::string filename;

    filename = basename;
    std::ifstream scanner(filename.append(".ele").c_str());
    scanner >> ntriangles;

    filename = basename;
    std::ifstream scannerperimeter(filename.append(".poly").c_str());
    scannerperimeter >> nsegments; // first line is number of nodes
    assert(nsegments == 0);  // standard triangle format, nodes == 0
    next_line(scannerperimeter);
    scannerperimeter >> nsegments;  // number of segments

    mesh.ntriangles = ntriangles;
    mesh.nsegments = nsegments;
    mesh.nelements = ntriangles + nsegments;
    mesh.maxnelements = maxfactor * mesh.nelements;

    printf("memory for elements: %lu MB\n", mesh.maxnelements * (sizeof(uint3) * 2 + sizeof(bool) * 2) / 1048576);
    mesh.elements.alloc(mesh.maxnelements);
    mesh.isdel.alloc(mesh.maxnelements);
    mesh.isbad.alloc(mesh.maxnelements);
    mesh.neighbours.alloc(mesh.maxnelements);

    uint3 *elements = mesh.elements.cpu_wr_ptr(true);
    bool *isdel = mesh.isdel.cpu_wr_ptr(true), *isbad = mesh.isbad.cpu_wr_ptr(true);
    for (i = 0; i < ntriangles; i++) {
        next_line(scanner);
        scanner >> index >> n1 >> n2 >> n3;
        if (firstindex) {
            assert(index == 0);
            firstindex = false;
        }

        elements[index].x = n1;
        elements[index].y = n2;
        elements[index].z = n3;
        isdel[index] = isbad[index] = false;

    }

    firstindex = true;
    for (i = 0; i < nsegments; i++) {
        next_line(scannerperimeter);
        scannerperimeter >> index >> n1 >> n2;
        if (firstindex) {
            assert(index == 0);
            firstindex = false;
        }

        elements[index + ntriangles].x = n1;
        elements[index + ntriangles].y = n2;
        elements[index + ntriangles].z = INVALIDID;
        isdel[index] = isbad[index] = false;
    }
}
