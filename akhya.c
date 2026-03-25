import random

# --- Global Data Setup (Simulating Input Raw DNA Sequence Data) ---

# A simple simulated 'raw' DNA sequence (A, T, C, G).
# Real sequences are millions of bases long, but we'll use a short one for demonstration.
RAW_SEQUENCE = "ATGCGTAGCTGAATCCGTAGCTTTTTAAGCTTCGCGTACGT"

# A simulated 'fragment' for assembly demonstration.
# In reality, assembly uses thousands of overlapping fragments.
FRAGMENT_A = "ATGCGTAGCTGAATCC"
FRAGMENT_B = "ATCCGTAGCTTTTT"
FRAGMENT_C = "TCCGTAGCTTTTTAAGCTTC"

# Simulated gene functions for Functional Annotation
FUNCTIONAL_DATABASE = {
    "SEQ_G1": "DNA Repair Enzyme (Simulation)",
    "SEQ_G2": "Silk Protein Component (Arachnid Specific)",
    "SEQ_G3": "Venom Toxin Receptor (Hypothetical)",
}

# --- Step 1 & 2: Quality Check & Genome Assembly (Simplified) ---

def quality_check(raw_data: str) -> str:
    """
    Simulates the 'Quality Check & Filtering' step.

    In a real pipeline, this step removes sequences with low-quality scores.
    Here, we simulate filtering out a known 'low-quality' pattern (e.g., 'TTTTT')
    and simplifying the string to ensure it's uppercase.
    """
    print("--- 1. Quality Check & Filtering ---")
    
    # 1. Standardize Case
    cleaned_data = raw_data.upper()
    print(f"Original Length: {len(raw_data)}")
    
    # 2. Simulate Filtering (removing a low-quality run)
    low_quality_pattern = "TTTTT"
    if low_quality_pattern in cleaned_data:
        cleaned_data = cleaned_data.replace(low_quality_pattern, "")
        print(f"Removed '{low_quality_pattern}' (simulated low-quality read).")
    
    print(f"Cleaned Sequence Length: {len(cleaned_data)}")
    return cleaned_data

def genome_assembly_simulation(fragments: list) -> str:
    """
    Simulates 'Genome Assembly'.

    This simplified function attempts to stitch three fragments together based
    on simple overlaps to reconstruct a longer 'contig' (contiguous sequence).
    """
    print("\n--- 2. Genome Assembly Simulation ---")
    
    # Simple assembly: B overlaps with A, and C overlaps with B (in a real scenario this is much harder).
    
    # Fragment A: ATGCGTAGCTGAATCC
    # Fragment B:       ATCCGTAGCTTTTT (Overlap on 'ATCC')
    # Fragment C:          TCCGTAGCTTTTTAAGCTTC (Overlap on 'TCCGTAGCTTTT')
    
    # Step A + B
    overlap_ab = "ATCC"
    assembled_ab = fragments[0] + fragments[1].split(overlap_ab, 1)[-1]
    
    # Step (A+B) + C
    overlap_bc = "TCCGTAGCTTTT"
    final_assembly = assembled_ab + fragments[2].split(overlap_bc, 1)[-1]
    
    print(f"Stitched {len(fragments)} fragments into a simulated contig.")
    print(f"Contig: {final_assembly[:50]}...") # Show beginning of the assembled sequence
    return final_assembly


# --- Step 3 & 4: Gene Prediction & Functional Annotation ---

def gene_prediction(contig: str) -> list:
    """
    Simulates 'Gene Prediction' using a simple pattern match.

    In reality, algorithms search for start/stop codons, open reading frames,
    and sequence features, but here we look for two specific 'gene' patterns.
    """
    print("\n--- 3. Gene Prediction ---")
    
    # Simplified 'gene' patterns we are looking for
    gene_pattern_1 = "GTAGCTGA"
    gene_pattern_2 = "CGTAGCT"
    
    predicted_genes = []
    
    if gene_pattern_1 in contig:
        predicted_genes.append(("SEQ_G1", contig.find(gene_pattern_1)))
        print(f"Found Gene 1 (ID: SEQ_G1) at position {contig.find(gene_pattern_1)}.")

    if gene_pattern_2 in contig:
        predicted_genes.append(("SEQ_G2", contig.find(gene_pattern_2)))
        print(f"Found Gene 2 (ID: SEQ_G2) at position {contig.find(gene_pattern_2)}.")

    # Always predict a third hypothetical gene to demonstrate the lookup failing
    # This gene is predicted, but its function is not known (yet).
    predicted_genes.append(("SEQ_G3", contig.find("TCGCGTACGT")))
    
    return predicted_genes

def functional_annotation(gene_list: list, database: dict) -> dict:
    """
    Simulates 'Functional Annotation'.

    It maps predicted gene IDs to known functions stored in the database.
    This is essentially a dictionary lookup.
    """
    print("\n--- 4. Functional Annotation ---")
    annotation_results = {}
    
    for gene_id, location in gene_list:
        function = database.get(gene_id, "Function Unknown (No Match in Database)")
        annotation_results[gene_id] = {
            "location": location,
            "function": function
        }
        print(f"- Gene ID: {gene_id} | Function: {function}")
        
    return annotation_results

# --- Step 5: Comparative Genomics & Phylogenetic Analysis ---

def calculate_hamming_distance(seq1: str, seq2: str) -> int:
    """
    Calculates the Hamming Distance between two sequences of equal length.
    This is a simple metric for comparing how 'different' two sequences are.
    """
    if len(seq1) != len(seq2):
        # We assume sequences are pre-aligned (a step in Comparative Genomics)
        return -1 

    distance = 0
    for base1, base2 in zip(seq1, seq2):
        if base1 != base2:
            distance += 1
    return distance

def phylogenetic_analysis(target_genome: str):
    """
    Simulates 'Comparative Genomics' and 'Phylogenetic Analysis'.

    We compare our target genome to two reference species (simulated)
    to determine its closest relative based on sequence similarity.
    """
    print("\n--- 5. Comparative Genomics & Phylogenetic Analysis ---")

    # The genomes have been 'aligned' (a prior step) and are now the same length
    reference_genome_spider = target_genome.replace("A", "C", 1).replace("G", "T", 1) # Low difference (closer relative)
    reference_genome_scorpion = target_genome.replace("A", "T").replace("C", "G") # High difference (more distant)

    distance_spider = calculate_hamming_distance(target_genome, reference_genome_spider)
    distance_scorpion = calculate_hamming_distance(target_genome, reference_genome_scorpion)
    
    # Distance is proportional to evolutionary time/difference
    
    print(f"Target Genome vs. Reference Spider: {distance_spider} differences (Low Distance = High Similarity)")
    print(f"Target Genome vs. Reference Scorpion: {distance_scorpion} differences (High Distance = Low Similarity)")
    
    # Draw a simple conclusion
    if distance_spider < distance_scorpion:
        conclusion = "Conclusion: The target organism is evolutionarily closer to the Spider reference."
    elif distance_spider > distance_scorpion:
        conclusion = "Conclusion: The target organism is evolutionarily closer to the Scorpion reference."
    else:
        conclusion = "Conclusion: Evolutionary distance is equal or undetermined."

    print("-" * 50)
    print(conclusion)
    print("-" * 50)
    
    return conclusion

# --- Step 6: Output Visual Reports ---

def generate_reports(annotations: dict, phylo_conclusion: str):
    """
    Simulates 'Output Visual Reports' by generating a summary.
    """
    print("\n--- 6. Output Visual Reports ---")
    print("--- Final Analysis Summary ---")
    
    print("\n[Gene Annotation Report]")
    for gene_id, data in annotations.items():
        print(f"  {gene_id}: {data['function']} (Located at index {data['location']})")

    print("\n[Phylogenetic Report]")
    print(f"  Evolutionary Finding: {phylo_conclusion}")
    print("\nAnalysis Complete.")


# --- Main Pipeline Execution ---

def run_genetic_pipeline():
    """
    Executes the entire simulated genetic analysis pipeline sequentially.
    """
    # 1. Quality Check & Filtering
    filtered_data = quality_check(RAW_SEQUENCE)
    
    # 2. Genome Assembly
    fragments_to_assemble = [FRAGMENT_A, FRAGMENT_B, FRAGMENT_C]
    assembled_contig = genome_assembly_simulation(fragments_to_assemble)

    # 3. Gene Prediction
    predicted_genes = gene_prediction(assembled_contig)
    
    # 4. Functional Annotation
    annotated_results = functional_annotation(predicted_genes, FUNCTIONAL_DATABASE)
    
    # 5. Comparative Genomics & Phylogenetic Analysis
    phylo_conclusion = phylogenetic_analysis(assembled_contig)
    
    # 6. Output Reports
    generate_reports(annotated_results, phylo_conclusion)


if __name__ == "__main__":
    # Execute the pipeline when the script is run
    run_genetic_pipeline()